#pragma once

#include "src/Network/DataTransferProtocolAsh/dtparequest.h"

#include "src/performancebenchmark.h"   //DELETE

class AuthenticationSystem : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AuthenticationSystem)
public:
    explicit AuthenticationSystem(QObject *parent = nullptr);

    static AuthenticationSystem* getInstance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

public:
    enum class AuthenticationErrors
    {
        NO_ERROR,
        WRONG_PASSWORD_EMAIL            //The password or the email are wronged
    };

    Q_ENUM(AuthenticationErrors)
    //Try to authenticate
    Q_INVOKABLE void loginEmail(QString email, QString password, QObject *qmlAreaLogin);
    Q_INVOKABLE void registerEmail(QString email, QString password, QObject *qmlAreaRegister);

    static void loginEmailResult(DTPARequest *request, bool *deleteRequest);
    static void registerEmailResult(DTPARequest *request, bool *deleteRequest);
private:
    static QQmlEngine *_engine;

    static QObject *_qmlAreaLogin;
    static QObject *_qmlAreaRegister;
};

