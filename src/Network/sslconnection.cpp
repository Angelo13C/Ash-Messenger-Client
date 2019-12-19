#include "sslconnection.h"

#include <QEventLoop>
#include <QSslError>
#include <QSsl>
#include <QHostAddress>

#include "DataTransferProtocolAsh/dtpareceiver.h"
#include "DataTransferProtocolAsh/dtpasender.h"

#include "src/Other/config.h"

#include "DataTransferProtocolAsh/dtpa.h"

SslConnection::SslConnection(QObject *parent) : QObject(parent)
{
    //Get values from JSON config
    _SERVER_ADDRESS = Config::readValue("network/server_address");
    _SERVER_PORT = Config::readValue("network/server_port").toUShort();
    _MS_RECONNECT_SOCKET = Config::readValue("network/ms_reconnect_socket").toUShort();
}

void SslConnection::initialize(QThread *thread)
{
    connect(thread, &QThread::started, this, &SslConnection::runThread);
}

//Run the sender thread, to get it working
void SslConnection::runThread()
{
    connectToServer();

    //Run the event loop
    QEventLoop loop;
    connect(this->thread(), &QThread::finished, &loop, &QEventLoop::quit);
    loop.exec();
}

//Delete the socket from the heap at the end
SslConnection::~SslConnection()
{
    _socket->deleteLater();
}

//Try to connect to the server
void SslConnection::connectToServer()
{
    _socket = new QSslSocket(this);
    DTPASender::getInstance()->setSocket(_socket);

    _socket->setProtocol(QSsl::TlsV1_0);

    connect(_socket, &QSslSocket::encrypted, this, &SslConnection::onReady);
    connect(_socket, &QSslSocket::disconnected, this, &SslConnection::onDisconnect);
    connect(_socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onError(QList<QSslError>)));

    //If the socket can't connect the first time, automatically try to connect every MS_RECONNECT_SOCKET milliseconds
    while(true)
    {
        //Try to connect to the server
        _socket->connectToHostEncrypted(_SERVER_ADDRESS, _SERVER_PORT);

        _socket->waitForConnected(_MS_RECONNECT_SOCKET);

        qDebug() << "Socket state: " << _socket->state();
        //Break if the connection is succesfull, otherwise wait
        if(_socket->state() == QAbstractSocket::ConnectedState)
            break;
        else
            QThread::msleep(_MS_RECONNECT_SOCKET);
    }

    _socket->startClientEncryption();

    if(!_socket->waitForEncrypted() && _socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << _socket->error();
        return;
    }
}

//When the socket is connected succesfully
void SslConnection::onReady()
{
    connect(_socket, &QSslSocket::readyRead, this, &SslConnection::read);
}

//On socket error
void SslConnection::onError(QList<QSslError> errors)
{
    _socket->ignoreSslErrors(errors);
    //qDebug() << errors;           //If you want to see errors, uncomment this
}

//On disconnect, fre the heap and try to reconnect
void SslConnection::onDisconnect()
{
    _socket->deleteLater();
    connectToServer();
}

//Read a packet from the socket and add the request to DTPAReceiver cached packets
void SslConnection::read()
{
    QString packet = readSocket();

    //If a packet is completely available
    if(packet != "")
    {
        QList<DTPARequest> requests = DTPAReceiver::packetToRequests(packet);

        for(DTPARequest &request : requests)
        {
            DTPAReceiver::addToCachedRequests(request);
        }
    }
}

//Read from the socket solving bugs
QString SslConnection::readSocket()
{
    /*This is for solving the bug that the client reads more than it should from the socket
      Sometimes it reads a part of the next packet also because the current packet is shorter than
      the max size (4096)*/

    _cachedBytePacket += _socket->read(DTPA::REQUEST_MAX_SIZE - _cachedBytePacket.length());

    QString packet = _cachedBytePacket;
    int n = packet.length() > DTPA::REQUEST_MAX_SIZE ? DTPA::REQUEST_MAX_SIZE : packet.length();

    //Check if the last ascii char of the packet is a bugged one (it's only the first byte of a pair of an extended ascii char)
    while(packet.at(n - 1) == 65533)
    {
        packet.remove(n - 1, 1);
        n--;
    }
    //Remove the all the characters except the ones that aren't been full read
    _cachedBytePacket.remove(0, packet.toUtf8().length());

    packet = _cachedPacket + packet;

    int indexDelimiterCount = 0;
    int indexDelimiter = 0;
    int lastIndexDelimiter = 0;
    //Check how many fragments' delimiters (~) are in the packet
    while(true)
    {
        indexDelimiter = packet.indexOf(DTPA::TOKEN_FRAGMENT_DELIMITER, indexDelimiter);

        if(indexDelimiter == -1)
            break;

        indexDelimiter++;

        if(!DTPA::isByteStuffed(packet.mid(lastIndexDelimiter, indexDelimiter), indexDelimiter - lastIndexDelimiter - 1))
        {
            indexDelimiterCount++;

            lastIndexDelimiter = indexDelimiter - 1;
        }
    }
    if(indexDelimiterCount < 2)
    {
        _cachedPacket = packet;
        return "";
    }
    //If there is an uncomplete request in the packet, take only the completed ones
    else
    {
        int n = indexDelimiterCount % 2 ? -1 : 1;
        _cachedPacket = packet.mid(lastIndexDelimiter + n + 1);

        //Remove all characters from lastIndexDelimiter
        packet.remove(lastIndexDelimiter + n + 1, packet.length() - lastIndexDelimiter + 1);
        _cachedBytePacket.remove(0, lastIndexDelimiter);
    }

    return packet;
}
