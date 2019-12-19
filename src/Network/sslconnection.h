#pragma once

#include <QSslSocket>

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

    QString _SERVER_ADDRESS;
    quint16 _SERVER_PORT, _MS_RECONNECT_SOCKET;

    QString readSocket();
};

