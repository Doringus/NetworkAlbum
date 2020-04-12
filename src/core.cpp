#include "core.h"

#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>

#include "action/actionprovider.h"
#include "base/dispatcher.h"
#include "store/mainstore.h"
#include "store/clientstore.h"

Core::Core(QObject *parent) : QObject(parent) {
    qRegisterMetaType<qintptr>("qintptr");
    qRegisterMetaType<bool>("bool");
    m_SessionFactory = new SessionFactory(this);
    m_NetworkAccessMiddleware = new NetworkAccessMiddleware(this);
    m_ClientNetworkMiddleware = new ClientNetworkAccessMiddleware(this);
    QFontDatabase font;
    if(font.addApplicationFont(":/res/fonts/fontawesome-webfont.ttf") == -1) {
            qWarning() << "Failed to load font";
    }
    qmlRegisterSingletonType<ActionProvider>("NetworkAlbum", 1, 0, "ActionProvider",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&ActionProvider::get(), QQmlEngine::CppOwnership);
        return &ActionProvider::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    qmlRegisterSingletonType<ActionProvider>("NetworkAlbum", 1, 0, "MainStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&MainStore::get(), QQmlEngine::CppOwnership);
        return &MainStore::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    qmlRegisterSingletonType<ActionProvider>("NetworkAlbum", 1, 0, "ClientStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&ClientStore::get(), QQmlEngine::CppOwnership);
        return &ClientStore::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    Dispatcher::get().addStore(QSharedPointer<MainStore>(&MainStore::get(), [](MainStore*){}));
    Dispatcher::get().addStore(QSharedPointer<ClientStore>(&ClientStore::get(), [](ClientStore*){}));
    /// \warning Dont change the middlewares registration order
    Dispatcher::get().addMiddleware(QSharedPointer<SessionFactory>(m_SessionFactory, [](SessionFactory*){}));
    Dispatcher::get().addMiddleware(QSharedPointer<NetworkAccessMiddleware>(m_NetworkAccessMiddleware, [](NetworkAccessMiddleware*){}));
    Dispatcher::get().addMiddleware(QSharedPointer<ClientNetworkAccessMiddleware>(m_ClientNetworkMiddleware, [](ClientNetworkAccessMiddleware*){}));
}
