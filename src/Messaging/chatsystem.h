#pragma once

#include "src/Network/DataTransferProtocolAsh/dtparequest.h"

class ChatSystem : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatSystem)
public:
    explicit ChatSystem(QObject *parent = nullptr);

    static ChatSystem* getInstance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

public:
    Q_INVOKABLE void createPrivateChat(int chatID);
    static void newPrivateChat(DTPARequest *request, bool *deleteRequest);
    static void addUserToChat(int chatID, int userID);

private:
    static QObject *_qmlAreaChatList;
    static QMap<int, int> _chatIDs;  //Key: sql chat id, Value: qml chat id

public:
    Q_INVOKABLE void setQmlChatListInstance(QObject *qmlChatList);

    Q_INVOKABLE void loadQmlChats(bool blocking = true);
    static void addQmlChat(int sqlChatID, QString chatName, QString chatImagePath, bool blocking = true);
    static void setQmlChatMessage(int sqlChatID, QString blueMessage, QString message, QString timeStamp);
};

