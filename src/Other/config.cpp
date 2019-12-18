#include "config.h"

//Initialize the config reading the config.json
void Config::initialize()
{
    QFile configFile(":/CONFIG/Config/config.json");
    configFile.open(QIODevice::ReadOnly);

    _configDoc = QJsonDocument::fromJson(configFile.readAll());

    configFile.close();
}

//Read the value associated to the json file with that key
QString Config::readValue(QString rawKey)
{
    //Separate keys by /
    QStringList separatedKeys = rawKey.split("/");

    QJsonObject valuesObject = _configDoc.object();

    //Go through all the objects with that key
    for(QString key : separatedKeys) {
        valuesObject = valuesObject[key].toObject();
    }

    //Get the value of the last part of the raw key
    return valuesObject[separatedKeys.last()].toString();
}
