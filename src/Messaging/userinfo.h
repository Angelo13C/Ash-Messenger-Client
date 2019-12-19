#pragma once

namespace UserInfo
{
void initialize();

extern int _clientUserID;
void setClientUserID(int userID);
int getClientUserID();

bool getUserInfo(QString userID, QString *name, QString *username, QString *picturePath);
void saveUserInfo(int userID, QString name, QString username, QString picturePath);
};

