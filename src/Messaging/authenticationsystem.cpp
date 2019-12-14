#include "authenticationsystem.h"

AuthenticationSystem::AuthenticationSystem(QObject *parent) : QObject(parent)
{
    DTPAReceiverManager::getInstance()->signCommandFunction(DTPARequest::Command::LOGIN_USER_EMAIL_RESULT, loginEmailResult);
    DTPAReceiverManager::getInstance()->signCommandFunction(DTPARequest::Command::REGISTER_USER_EMAIL_RESULT, registerEmailResult);
}

/* SINGLETON */

AuthenticationSystem* AuthenticationSystem::getInstance()
{
    static AuthenticationSystem *instance = new AuthenticationSystem();
    return instance;
}

QQmlEngine *AuthenticationSystem::_engine;
QObject *AuthenticationSystem::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)

    _engine = engine;

    return getInstance();
}

/* TRY AUTHENTICATION WITH EMAIL AND PASSWORD */

QObject *AuthenticationSystem::_qmlAreaLogin;  //The Area Login qml object
void AuthenticationSystem::loginEmail(QString email, QString password, QObject *qmlAreaLogin)
{
    _qmlAreaLogin = qmlAreaLogin;

    DTPARequest request(DTPARequest::Command::LOGIN_USER_EMAIL, QStringList(), DTPARequest::Priority::HIGH);

    request.addNewForm(&email);
    request.addNewForm(&password);

    DTPASender::getInstance()->sendRequest(&request);
}

QObject *AuthenticationSystem::_qmlAreaRegister;  //The Area Login qml object
void AuthenticationSystem::registerEmail(QString email, QString password, QObject *qmlAreaRegister)
{
    _qmlAreaRegister = qmlAreaRegister;

    DTPARequest request(DTPARequest::Command::REGISTER_USER_EMAIL, QStringList(), DTPARequest::Priority::HIGH);

    request.addNewForm(&email);
    request.addNewForm(&password);

    DTPASender::getInstance()->sendRequest(&request);
}

//The result of the login with email
void AuthenticationSystem::loginEmailResult(DTPARequest *request, bool *deleteRequest)
{
    if(request->isComplete())
    {
        //Delete the request
        *deleteRequest = true;

        QString userID = request->getForms().first().getValue();
        //If the user id is valid
        if(userID != "-1")
            UserInfo::setClientUserID(userID.toInt());

        QMetaObject::invokeMethod(_qmlAreaLogin, "loginResult",
                Q_ARG(QVariant, userID != "-1"));
    }
}

void AuthenticationSystem::registerEmailResult(DTPARequest *request, bool *deleteRequest)
{
    if(request->isComplete())
    {
        //Delete the request
        *deleteRequest = true;

        QString userID = request->getForms().first().getValue();
        //If the user id is valid
        if(userID != "-1")
            UserInfo::setClientUserID(userID.toInt());

        QMetaObject::invokeMethod(_qmlAreaRegister, "registerResult",
                Q_ARG(QVariant, userID != "-1"));
    }
}
