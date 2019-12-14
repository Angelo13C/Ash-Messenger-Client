#include "sslconnection.h"

SslConnection::SslConnection(QObject *parent) : QObject(parent)
{

}

void SslConnection::initialize(QThread *thread)
{
    connect(thread, &QThread::started, this, &SslConnection::runThread);
}

//Run the sender thread, to get it working
void SslConnection::runThread()
{
    connectToServer();
    DTPASender::getInstance()->setSocket(_socket);

    //Send packet if needed or wait 1 ms
    while(true)
    {
        if(DTPASender::getInstance()->queueEmpty())
            QThread::msleep(1);
        else
            DTPASender::getInstance()->sendPacket();

        QCoreApplication::processEvents();
    }
}

//Delete the socket from the heap at the end
SslConnection::~SslConnection()
{
    delete _socket;
}

void SslConnection::connectToServer()
{
    _socket = new QSslSocket(this);
    _socket->setProtocol(QSsl::TlsV1_0);

    connect(_socket, &QSslSocket::encrypted, this, &SslConnection::onReady);
    connect(_socket, &QSslSocket::disconnected, this, &SslConnection::onDisconnect);
    connect(_socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onError(QList<QSslError>)));

    //Get values from JSON config
    const QString SERVER_ADDRESS = Config::readValue("networking/server_address");
    const quint16 SERVER_PORT = Config::readValue("networking/server_port").toUShort();
    const quint16 MS_RECONNECT_SOCKET = Config::readValue("networking/ms_reconnect_socket").toUShort();

    //Try to connect to the server
    _socket->connectToHostEncrypted(SERVER_ADDRESS, SERVER_PORT);

    _socket->waitForEncrypted();

    //If the socket can't connect the first time, automatically try to connect every MS_RECONNECT_SOCKET milliseconds
    while(_socket->state()!=QAbstractSocket::ConnectedState)
    {
        QThread::msleep(MS_RECONNECT_SOCKET);

        _socket->connectToHostEncrypted(SERVER_ADDRESS, SERVER_PORT);

        _socket->waitForConnected(MS_RECONNECT_SOCKET);
    }

    _socket->startClientEncryption();

    if(!_socket->waitForEncrypted() && _socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << _socket->error();
        return;
    }
}

void SslConnection::onReady()
{
    connect(_socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void SslConnection::onError(QList<QSslError> errors)
{
    _socket->ignoreSslErrors(errors);
    //qDebug() << errors;           //If you want to see errors, uncomment this
}

void SslConnection::onDisconnect()
{
    connectToServer();
}

QString SslConnection::readSocket()
{
    /*This is for solving the bug that the client reads more than it should from the socket
      Sometimes it reads a part of the next packet also because the current packet is shorter than
      the max size (4096)*/

    _cachedBytePacket += _socket->read(DTPA::REQUEST_MAX_SIZE - _cachedBytePacket.length());
    std::string temp = _cachedBytePacket.toStdString();

    QString packet = QString::fromStdString(temp);
    int n = packet.length() > DTPA::REQUEST_MAX_SIZE ? DTPA::REQUEST_MAX_SIZE : packet.length();

    //Check if the last ascii char of the packet is a bugged one (it's only the first byte of a pair of an extended ascii char)
    while(packet[n - 1] == 65533)
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

void SslConnection::read()
{
    QString packet = readSocket();

    //If a packet is completely available
    if(packet != "")
    {
        QList<DTPARequest> requests = DTPAReceiver::packetToRequests(packet);

        for(int i = 0; i < requests.length(); i++)
        {
            DTPARequest request = DTPARequest(requests.at(i));
            DTPAReceiver::addToCachedRequests(request);
        }
    }
}
