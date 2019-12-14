#include "searchchatuser.h"

SearchChatUser::SearchChatUser(QObject *parent) : QObject(parent)
{
    DTPAReceiverManager::getInstance()->signCommandFunction
            (DTPARequest::Command::SEARCH_USERNAME_RESULT, searchUsernameResult);

    DTPAReceiverManager::getInstance()->signCommandFunction
            (DTPARequest::Command::GET_USER_INFO_RESULT, getUserInfoResult);
}

/* SINGLETON */

SearchChatUser* SearchChatUser::getInstance()
{
    static SearchChatUser *instance = new SearchChatUser();
    return instance;
}

QObject *SearchChatUser::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return getInstance();
}

//Set the Area Search QML Object
QObject *SearchChatUser::_qmlAreaSearch;
void SearchChatUser::setAreaObect(QObject *areaObject)
{
    _qmlAreaSearch = areaObject;
}
#include <QDebug>   //DELETe
QVector<int> SearchChatUser::_searchedUsersID;
void SearchChatUser::searchUsername(QString username)
{
    //Remove the searched users ID from the vector
    _searchedUsersID.clear();
    _searchedUsersID.squeeze();

    //Remove the '@' char
    username.remove(0, 1);

    DTPARequest request(DTPARequest::Command::SEARCH_USERNAME, QStringList() << username,
                        DTPARequest::Priority::HIGH);

    DTPASender::getInstance()->sendRequest(&request);
}

void SearchChatUser::searchUsernameResult(DTPARequest *request, bool *deleteRequest)
{
    if(request->isComplete())
    {
        //Delete the request after this function
        *deleteRequest = true;

        //Get the user id from the request
        QString userID = request->getForms().first().getValue();

        QString name, username, picturePath;
        //If the user info are saved
        if(UserInfo::getUserInfo(userID, &name, &username, &picturePath))
        {
            //Clear the list if the last search ID is not equal to the new one
            showSearch(name, username, picturePath);
        }
        else
        {
            _searchedUsersID.append(userID.toInt());
        }
    }
}

void SearchChatUser::getUserInfoResult(DTPARequest *request, bool *deleteRequest)
{
    if(request->isComplete())
    {
        *deleteRequest = true;

        QString userID = request->getForms().at(0).getValue();
        //If the user with that ID was new in the Database
        if(_searchedUsersID.removeAll(userID.toInt()) > 0)
        {
            QString name = request->getForms().at(1).getValue();
            QString username = request->getForms().at(2).getValue();
            QString picPath = request->getForms().at(3).getValue();

            //Instead of false, put the real value
            showSearch(name, username, picPath);
        }
    }
}

//Add element to the list of searched users with that username
void SearchChatUser::showSearch(QString name, QString username, QString picPath)
{
    if(_qmlAreaSearch == nullptr)
        return;

    QMetaObject::invokeMethod(_qmlAreaSearch, "showSearchResult",
              Q_ARG(QVariant, name),
              Q_ARG(QVariant, username),
              Q_ARG(QVariant, picPath));
}

