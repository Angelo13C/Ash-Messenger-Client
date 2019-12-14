#pragma once
#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>

class SingleAppInstance : public QObject
{
    Q_OBJECT
public:
    explicit SingleAppInstance(QObject *parent = nullptr);

    bool isRunning();
    void listen();

private:
    static constexpr int WAIT_INSTANCE_TIME = 20;
    const QString _instanceName = "com.Phoenix.Ash";

signals:
    void newInstance();

private:
    QLocalServer _server;
};

