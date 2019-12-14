#include "usersettings.h"

//Save on permanent memory things
void UserSettings::SaveSettings(Key key, QString value)
{
    QSettings settings("Phoenix Software", "Ash");
    settings.beginGroup("AuthenticationSection");

    //Save parameter value
    settings.setValue(static_cast<QString>(static_cast<int>(key)), value);

    settings.endGroup();
}

QString UserSettings::GetSetting(Key key, QString defaultValue)
{
    QSettings settings("Phoenix Software", "Ash");
    settings.beginGroup("AuthenticationSection");

    //Return the readed value as a string
    return settings.value(static_cast<QString>(static_cast<int16_t>(key)), defaultValue).toString();
}
