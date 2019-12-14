#include "advertisepanel.h"

AdvertisePanel::AdvertisePanel(QObject *parent) : QObject(parent)
{

}

/* SINGLETON */

AdvertisePanel* AdvertisePanel::getInstance()
{
    static AdvertisePanel *instance = new AdvertisePanel();
    return instance;
}

QObject *AdvertisePanel::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return getInstance();
}

void AdvertisePanel::openBrowserURL(QString url)
{
    QDesktopServices::openUrl(QUrl("http://" + url));
}
