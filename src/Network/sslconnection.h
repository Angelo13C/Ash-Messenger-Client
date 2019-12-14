#pragma once

#include <QObject>
#include <QThread>

#include <QSslSocket>
#include <QList>
#include <QSslError>
#include <QHostAddress>
#include <QSsl>

#include "DataTransferProtocolAsh/dtpareceiver.h"

#include "src/Other/config.h"

class SslConnection : public QObject
{
    Q_OBJECT
public:
    explicit SslConnection(QObject *parent = nullptr);
    ~SslConnection();

    void initialize(QThread *thread);

signals:
    void onRead(QByteArray);

public slots:
    void runThread();

    void connectToServer();
    void onReady();
    void onError(QList<QSslError> errors);
    void onDisconnect();

    void read();

private:
    QSslSocket *_socket;
    QString _cachedPacket = "";
    QByteArray _cachedBytePacket = "";

    QString readSocket();
};

