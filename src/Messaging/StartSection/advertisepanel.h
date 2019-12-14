#pragma once

#include <QQmlEngine>
#include <QObject>
#include <QDesktopServices>

class AdvertisePanel : public QObject
{
    Q_OBJECT
public:
    explicit AdvertisePanel(QObject *parent = nullptr);

    static AdvertisePanel* getInstance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);


    Q_INVOKABLE void openBrowserURL(QString url);
signals:

public slots:
};

