#include <QGuiApplication>
#include <QThreadPool>

#include <QQuickStyle>

#include <QApplication>
#include <QWidget>
#include <QMainWindow>

#include "Other/config.h"
#include "Other/translatormanager.h"
#include "Other/singleappinstance.h"

#include "Database/database.h"

#include "Network/DataTransferProtocolAsh/dtpasender.h"
#include "Network/sslconnection.h"

#include "src/Messaging/StartSection/advertisepanel.h"
#include "src/Messaging/authenticationsystem.h"
#include "src/Messaging/chatsystem.h"
#include "src/Messaging/searchchatuser.h"
#include "src/Messaging/messagesystem.h"

//#define SINGLETON_APPLICATION     //Uncomment to remove the single instance application functionality

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Phoenix Software");
    QCoreApplication::setOrganizationDomain("PhoenixSoftware.com");
    QCoreApplication::setApplicationName("Ash (Messenger)");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    //Singleton application
    #ifdef SINGLETON_APPLICATION
    SingleAppInstance instance;
    if(instance.isRunning())
        return 0;

    instance.listen();
    app.connect(&instance, &SingleAppInstance::newInstance, &app, [&]() {
        for(QWindow *win : app.allWindows())
        {
            Qt::WindowFlags fl = win->flags();
            win->setFlags(win->flags() | Qt::WindowStaysOnTopHint);
            win->setFlags(fl);
        }
    });
    #endif

    Config::initialize();

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/QML/Qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    //Translator manager
    qmlRegisterSingletonType<TranslatorManager>("TranslatorManager", 1, 0, "TranslatorManager", TranslatorManager::qmlInstance);

    TranslatorManager::getInstance()->initialize(&engine);

    //Start networking sender thread
    QThread *networkThread = new QThread();
    app.connect(&app, &QApplication::lastWindowClosed, networkThread, &QThread::quit);

    //Connect to the server (must be a pointer for a problem of multi-threading)
    SslConnection *_connection = new SslConnection();

    _connection->initialize(networkThread);
    _connection->moveToThread(networkThread);
    networkThread->start();

    //Initialize the local database
    Database::initialize();

    //Register QML custom types
    qmlRegisterSingletonType<AdvertisePanel>("AdvertisePanel", 1, 0, "AdvertisePanel", AdvertisePanel::qmlInstance);
    qmlRegisterSingletonType<AuthenticationSystem>("AuthenticationSystem", 1, 0, "AuthenticationSystem", AuthenticationSystem::qmlInstance);
    qmlRegisterSingletonType<ChatSystem>("ChatSystem", 1, 0, "ChatSystem", ChatSystem::qmlInstance);
    qmlRegisterSingletonType<SearchChatUser>("SearchChatUser", 1, 0, "SearchChatUser", SearchChatUser::qmlInstance);
    qmlRegisterSingletonType<MessageSystem>("MessageSystem", 1, 0, "MessageSystem", MessageSystem::qmlInstance);

    engine.load(url);       //Load qml objects

    return app.exec();
}

