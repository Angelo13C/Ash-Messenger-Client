#pragma once

#include <QTranslator>

class TranslatorManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TranslatorManager)

public:
    enum class Location : int
    {
        AUTO = 0,
        UNITED_KINGDOM,
        ITALY
    };
    Q_ENUM(Location)                //(enum visible from qml files)

    explicit TranslatorManager(QObject *parent = nullptr);

    static TranslatorManager* getInstance();                //Singleton
    void initialize(QQmlApplicationEngine* qmlEngine);      //Set the engine to refresh translations

    Location getLanguage();                                   //Get current language
    Q_INVOKABLE void setLanguage(const Location location);      //Set current language (function visible from qml files)

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);           //Qml singleton

private:
    QQmlApplicationEngine *_qmlEngine;
    QTranslator _translator;

    Location _currentLocation = Location::UNITED_KINGDOM;

    QLocale _qlocale;

    QString getLanguagePath(TranslatorManager::Location location);
    TranslatorManager::Location getOSLocation();
};

