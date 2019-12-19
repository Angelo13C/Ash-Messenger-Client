#pragma once

class MessageSystem : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MessageSystem)
public:
    explicit MessageSystem(QObject *parent = nullptr);

    static MessageSystem* getInstance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    Q_INVOKABLE void sendTextMessage(QString chatID, QString text);

signals:

public slots:
};

