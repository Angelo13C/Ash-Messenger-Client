#include "messagesystem.h"

#include "src/Network/DataTransferProtocolAsh/dtparequest.h"
#include "src/Network/DataTransferProtocolAsh/dtpasender.h"

MessageSystem::MessageSystem(QObject *parent) : QObject(parent)
{

}

/* SINGLETON */

MessageSystem* MessageSystem::getInstance()
{
    static MessageSystem *instance = new MessageSystem();
    return instance;
}

QObject *MessageSystem::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return getInstance();
}

//Send a text message to a chat
void MessageSystem::sendTextMessage(QString chatID, QString text)
{
    DTPARequest request(DTPARequest::Command::SEND_TEXT_MESSAGE, DTPARequest::Priority::HIGH);

    request.addNewForm(&chatID);
    request.addNewForm(&text);

    DTPASender::getInstance()->sendRequest(&request);
}
