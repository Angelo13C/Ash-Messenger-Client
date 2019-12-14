#pragma once
#include <QSettings>
#include <QString>

namespace UserSettings
{
enum class Key
{
    LANGUAGE = 1
};

void SaveSettings(Key key, QString value);
QString GetSetting(Key key, QString defaultValue = "");
}

