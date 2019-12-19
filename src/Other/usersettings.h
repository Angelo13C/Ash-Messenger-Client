#pragma once
#include <QSettings>

namespace UserSettings
{
enum class Key
{
    LANGUAGE = 1
};

void SaveSettings(Key key, QString value);
QString GetSetting(Key key, QString defaultValue = "");
}

