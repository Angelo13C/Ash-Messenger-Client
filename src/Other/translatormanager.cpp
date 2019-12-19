#include "translatormanager.h"

#include <QtGui>
#include <QLocale>

#include "usersettings.h"

TranslatorManager::TranslatorManager(QObject *parent) :
    QObject(parent)
{


}

/* SETUP */

void TranslatorManager::initialize(QQmlApplicationEngine *qmlEngine)
{
    _qmlEngine = qmlEngine;
    bool ok;
    //Get the saved on memory language that the user chose before (if there's no language set is as AUTO)
    QString string = UserSettings::GetSetting(UserSettings::Key::LANGUAGE, QString::number(static_cast<int>(TranslatorManager::Location::AUTO)));

    int language = string.toInt(&ok);

    if (ok)
        setLanguage(static_cast<Location>(language));
}

/* SINGLETON */

TranslatorManager* TranslatorManager::getInstance()
{
    static TranslatorManager *instance = new TranslatorManager();
    return instance;
}

QObject *TranslatorManager::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return getInstance();
}

/* LANGUAGE */

TranslatorManager::Location TranslatorManager::getLanguage()
{
    return _currentLocation;
}

void TranslatorManager::setLanguage(const Location location)
{
    if (location != _currentLocation)
    {
        _currentLocation = location;

        if (location == Location::UNITED_KINGDOM)       //The default location is uk, so there isn't no file where to read the translation
        {
            qApp->removeTranslator(&_translator);
        }
        else
        {
            if (location == Location::AUTO)
            {
                _translator.load(":/Languages/Languages/lang_" + getLanguagePath(getOSLocation()));
            }
            else
            {
                _translator.load(":/Languages/Languages/lang_" + getLanguagePath(location));
            }

            qApp->installTranslator(&_translator);
        }

        UserSettings::SaveSettings(UserSettings::Key::LANGUAGE, QString::number(static_cast<int>(location)));          //Save default language
        _qmlEngine->retranslate();
    }
}

QString TranslatorManager::getLanguagePath(TranslatorManager::Location location)
{
    switch (location) {
    case TranslatorManager::Location::ITALY:
        return "it";

    //If the location isn't recognized
    default:
        qDebug() << "Location not recognized in getLanguagePath!!!";
        return nullptr;
    }
}

TranslatorManager::Location TranslatorManager::getOSLocation()
{
    switch(_qlocale.language())
    {
    case QLocale::Italian:
        return TranslatorManager::Location::ITALY;

    case QLocale::English:
        return TranslatorManager::Location::UNITED_KINGDOM;

    //Default location
    default:
        return TranslatorManager::Location::UNITED_KINGDOM;
    }
}
