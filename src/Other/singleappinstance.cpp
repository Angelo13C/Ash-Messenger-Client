#include "singleappinstance.h"

#include <QLocalSocket>

SingleAppInstance::SingleAppInstance(QObject *parent) : QObject(parent)
{    
    connect(&_server, &QLocalServer::newConnection, this, &SingleAppInstance::newInstance);
}

void SingleAppInstance::listen()
{
    _server.removeServer(_instanceName);
    _server.listen(_instanceName);
}

bool SingleAppInstance::isRunning()
{
    QLocalSocket socket;
    socket.connectToServer(_instanceName);

    bool connected = socket.waitForConnected(WAIT_INSTANCE_TIME);

    socket.close();
    socket.deleteLater();

    return connected;
}
