#pragma once

#include <QQmlEngine>
#include <QObject>

#include "src/Network/DataTransferProtocolAsh/dtpasender.h"
#include "userinfo.h"

class SearchChatUser : public QObject
{
    Q_OBJECT
public:
    explicit SearchChatUser(QObject *parent = nullptr);

    static SearchChatUser* getInstance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

public:

    Q_INVOKABLE void setAreaObect(QObject *areaObject);
    Q_INVOKABLE void searchUsername(QString username);
    static void searchUsernameResult(DTPARequest *request, bool *deleteRequest);
    static void getUserInfoResult(DTPARequest *request, bool *deleteRequest);

    static void showSearch(QString name, QString username, QString picPathh);
private:
    static QVector<int> _searchedUsersID;
    static QObject *_qmlAreaSearch;
};

