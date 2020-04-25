#include "core.h"

#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>

#include "action/actionprovider.h"
#include "base/dispatcher.h"
#include "store/clientstore.h"
#include "store/sessionsstore.h"
#include "store/rootstore.h"
#include "store/albumsstore.h"
#include "store/albumstore.h"

Core::Core(QObject *parent) : QObject(parent) {
    qRegisterMetaType<qintptr>("qintptr");
    qRegisterMetaType<bool>("bool");
    m_SessionFactory = new SessionFactory(this);
    m_NetworkAccessMiddleware = new NetworkAccessMiddleware(this);
    m_ClientNetworkMiddleware = new ClientNetworkAccessMiddleware(this);
    m_LinkMiddleware = new LinkMiddleware(this);
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
    qmlRegisterSingletonType<RootStore>("NetworkAlbum", 1, 0, "RootStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&RootStore::get(), QQmlEngine::CppOwnership);
        return &RootStore::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    qmlRegisterSingletonType<SessionsStore>("NetworkAlbum", 1, 0, "SessionsStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&SessionsStore::get(), QQmlEngine::CppOwnership);
        return &SessionsStore::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    qmlRegisterSingletonType<AlbumsStore>("NetworkAlbum", 1, 0, "AlbumsStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&AlbumsStore::get(), QQmlEngine::CppOwnership);
        return &AlbumsStore::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    qmlRegisterSingletonType<AlbumStore>("NetworkAlbum", 1, 0, "AlbumStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&AlbumStore::get(), QQmlEngine::CppOwnership);
        return &AlbumStore::get();
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

    Dispatcher::get().addStore(QSharedPointer<RootStore>(&RootStore::get(), [](RootStore*){}));
    Dispatcher::get().addStore(QSharedPointer<SessionsStore>(&SessionsStore::get(), [](SessionsStore*){}));
    Dispatcher::get().addStore(QSharedPointer<AlbumsStore>(&AlbumsStore::get(), [](AlbumsStore*){}));
    Dispatcher::get().addStore(QSharedPointer<AlbumStore>(&AlbumStore::get(), [](AlbumStore*){}));
    Dispatcher::get().addStore(QSharedPointer<ClientStore>(&ClientStore::get(), [](ClientStore*){}));
    /// \warning Dont change the middlewares registration order
    Dispatcher::get().addMiddleware(QSharedPointer<SessionFactory>(m_SessionFactory, [](SessionFactory*){}));
    Dispatcher::get().addMiddleware(QSharedPointer<LinkMiddleware>(m_LinkMiddleware, [](LinkMiddleware*){}));
    Dispatcher::get().addMiddleware(QSharedPointer<NetworkAccessMiddleware>(m_NetworkAccessMiddleware, [](NetworkAccessMiddleware*){}));
    Dispatcher::get().addMiddleware(QSharedPointer<ClientNetworkAccessMiddleware>(m_ClientNetworkMiddleware, [](ClientNetworkAccessMiddleware*){}));

    connect(&RootStore::get(), &RootStore::sessionCreated, this, &Core::onSessionCreated);
    connect(&ClientStore::get(), &ClientStore::connectedToAlbum, this, &Core::onConnectedToAlbum);
}

void Core::onSessionCreated() {
    Dispatcher::get().removeStore(QSharedPointer<Store>(&ClientStore::get(), [](ClientStore*){}));
    Dispatcher::get().removeMiddleware(QSharedPointer<Middleware>(m_ClientNetworkMiddleware, [](ClientNetworkAccessMiddleware*){}));
    disconnect(&RootStore::get(), &RootStore::sessionCreated, this, &Core::onSessionCreated);
}

void Core::onConnectedToAlbum() {
    Dispatcher::get().removeStore(QSharedPointer<Store>(&AlbumStore::get(), [](AlbumStore*){}));
    Dispatcher::get().removeStore(QSharedPointer<Store>(&AlbumsStore::get(), [](AlbumsStore*){}));
    Dispatcher::get().removeStore(QSharedPointer<Store>(&SessionsStore::get(), [](SessionsStore*){}));
    Dispatcher::get().removeMiddleware(QSharedPointer<Middleware>(m_NetworkAccessMiddleware, [](NetworkAccessMiddleware*){}));
    Dispatcher::get().removeMiddleware(QSharedPointer<Middleware>(m_LinkMiddleware, [](LinkMiddleware*){}));
    Dispatcher::get().removeMiddleware(QSharedPointer<Middleware>(m_SessionFactory, [](SessionFactory*){}));
    disconnect(&ClientStore::get(), &ClientStore::connectedToAlbum, this, &Core::onConnectedToAlbum);
}
