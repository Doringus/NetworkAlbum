#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>
#include <QSystemTrayIcon>

#include "base/action.h"
#include "base/dispatcher.h"
#include "store/linkstore.h"
#include "action/actionprovider.h"
#include "store/mainstore.h"
#include "middleware/sessionfactory.h"

enum class a {
    SAS,
    VAS
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QVariant v;
    Action action(a::SAS, v);
    QGuiApplication app(argc, argv);
    QFontDatabase font;
    if(font.addApplicationFont(":/res/fonts/fontawesome-webfont.ttf") == -1) {
            qWarning() << "Failed to load font";
    }
    SessionFactory sessionFactory;
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    qmlRegisterType<LinkStore>("NetworkAlbum", 1, 0, "LinkStore");
    qmlRegisterSingletonType<ActionProvider>("NetworkAlbum", 1, 0, "ActionProvider",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&ActionProvider::get(), QQmlEngine::CppOwnership);
        return &ActionProvider::get();
    });
    qmlRegisterSingletonType<ActionProvider>("NetworkAlbum", 1, 0, "MainStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&MainStore::get(), QQmlEngine::CppOwnership);
        return &MainStore::get();
    });
    Dispatcher::get().addStore(QSharedPointer<MainStore>(&MainStore::get(), [](MainStore*){}));
    Dispatcher::get().addMiddleware(QSharedPointer<SessionFactory>(&sessionFactory, [](SessionFactory*){}));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
