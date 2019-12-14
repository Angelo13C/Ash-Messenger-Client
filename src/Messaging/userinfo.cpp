#include "userinfo.h"


void UserInfo::initialize()
{
    //When user info result is received, save the info into the local database
    DTPAReceiverManager::getInstance()->signCommandFunction(
                DTPARequest::Command::GET_USER_INFO_RESULT, [](DTPARequest *req, bool *deleteRequest){
        if(req->isComplete())
        {
            *deleteRequest = true;

            saveUserInfo(req->getForms().at(0).getValue().toInt(),
            req->getForms().at(1).getValue(),
            req->getForms().at(2).getValue(),
            req->getForms().at(3).getValue());
        }
    });
}

int UserInfo::_clientUserID = -1;
//Set the user id of the client
void UserInfo::setClientUserID(int userID)
{
    _clientUserID = userID;
}

//Get the user id of the client
int UserInfo::getClientUserID()
{
    return _clientUserID;
}

void UserInfo::saveUserInfo(int userID, QString name, QString username, QString picturePath)
{
    Database::execute("INSERT INTO users (user_id, name, username, pic_path) VALUES (" + QString::number(userID)
                      + ",'" + name + "','" + username + "','" + picturePath + "')");
}

//Returns true if it has found the user with that userID, otherwise false
bool UserInfo::getUserInfo(QString userID, QString *name, QString *username, QString *picturePath)
{
    QVector<QStringList> result = Database::execute("SELECT name, username, pic_path FROM users "
            "WHERE user_id = " + userID + ";");

    //If the client hasn't saved the other user infos, get it from the server
    if(result.isEmpty())
    {
        DTPARequest req = DTPARequest(DTPARequest::Command::GET_USER_INFO,
                                      userID, DTPARequest::Priority::HIGH);
        DTPASender::getInstance()->sendRequest(&req);

        return false;
    }
    else
    {
        *name = result.at(0).at(0);
        *username = result.at(0).at(1);
        *picturePath = result.at(0).at(2);
        return true;
    }
}
