#include "chatsystem.h"

#include "src/Network/DataTransferProtocolAsh/dtpasender.h"
#include "src/Network/DataTransferProtocolAsh/dtpareceivermanager.h"

#include "src/Database/database.h"

#include "userinfo.h"

ChatSystem::ChatSystem(QObject *parent) : QObject(parent)
{
    UserInfo::initialize();
    DTPAReceiverManager::getInstance()->signCommandFunction(DTPARequest::Command::NEW_PRIVATE_CHAT, newPrivateChat);
}

/* SINGLETON */

ChatSystem* ChatSystem::getInstance()
{
    static ChatSystem *instance = new ChatSystem();
    return instance;
}

QObject *ChatSystem::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return getInstance();
}

void ChatSystem::createPrivateChat(int chatID)
{
    DTPARequest request = DTPARequest(DTPARequest::Command::CREATE_PRIVATE_CHAT,
            QStringList() << QString::number(chatID), DTPARequest::Priority::HIGH);

    DTPASender::getInstance()->sendRequest(&request);
}

void ChatSystem::newPrivateChat(DTPARequest *request, bool *deleteRequest)
{
    if(request->isComplete())
    {
        //Delete the received request
        *deleteRequest = true;

        //Create the chat in the local DB
        QString chatID = request->getForms().first().getValue();
        Database::execute("INSERT INTO chats (chat_id) VALUES(" + chatID + ");");
        Database::execute("INSERT INTO private_chats (chat_id) VALUES(" + chatID + ");");

        //Add the other user to the chat
        QString otherUserID = request->getForms().at(1).getValue();
        addUserToChat(chatID.toInt(), otherUserID.toInt());
        addUserToChat(chatID.toInt(), UserInfo::getClientUserID());

        QString name, username, picturePath;

        //If the client has saved the other user infos, show them
        if(UserInfo::getUserInfo(otherUserID, &name, &username, &picturePath))
        {
            addQmlChat(chatID.toInt(), name, picturePath);
        }
    }
}

//Add a user to a chat
void ChatSystem::addUserToChat(int chatID, int userID)
{
    //Create a new row of the table and add the user
    Database::execute("INSERT INTO users_in_chats(user_id, chat_id) VALUES (" +
                      QString::number(userID) + "," + QString::number(chatID) + ");");
}

QObject *ChatSystem::_qmlAreaChatList;  //The Area Chat List qml object
//Set the qml chat list instance of the object
void ChatSystem::setQmlChatListInstance(QObject *qmlChatList)
{
    _qmlAreaChatList = qmlChatList;
}

//Load saved chats from the local database
void ChatSystem::loadQmlChats(bool blocking)
{
    QVector<QStringList> privateChats = Database::execute("SELECT chat_id FROM private_chats;");

    foreach (QStringList chat, privateChats) {
        QVector<QStringList> resultUserID = Database::execute
                ("SELECT user_id FROM users_in_chats WHERE chat_id = " + chat.first() + ";");

        if(resultUserID.size() > 0)
        {
            QString userID = resultUserID.first().first();
            QString name, username, picturePath;
            if(UserInfo::getUserInfo(userID, &name, &username, &picturePath))
            {
                addQmlChat(chat.first().toInt(), name, picturePath, blocking);
            }
        }
    }
}

QMap<int, int> ChatSystem::_chatIDs;  //The Area Chat List qml object
//Add a qml chat view
void ChatSystem::addQmlChat(int sqlChatID, QString chatName, QString chatImagePath, bool blocking)
{
    Qt::ConnectionType conn = blocking ? Qt::BlockingQueuedConnection : Qt::AutoConnection;
    QVariant qmlChatID;
    QMetaObject::invokeMethod(_qmlAreaChatList, "addChat",
            conn,
            Q_RETURN_ARG(QVariant, qmlChatID),
            Q_ARG(QVariant, chatName),
            Q_ARG(QVariant, chatImagePath));

    _chatIDs.insert(sqlChatID, qmlChatID.toInt());
}

void ChatSystem::setQmlChatMessage(int sqlChatID, QString blueMessage, QString message, QString timeStamp)
{
    QMetaObject::invokeMethod(_qmlAreaChatList, "setChatMessage",
            Q_ARG(QVariant, sqlChatID),
            Q_ARG(QVariant, blueMessage),
            Q_ARG(QVariant, message),
            Q_ARG(QVariant, timeStamp));
}
