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

    Dispatcher::get().addStore("ClientStore", QSharedPointer<ClientStore>(&ClientStore::get(), [](ClientStore*){}));
    Dispatcher::get().addStore("RootStore", QSharedPointer<RootStore>(&RootStore::get(), [](RootStore*){}));
    Dispatcher::get().addStore("SessionsStore", QSharedPointer<SessionsStore>(&SessionsStore::get(), [](SessionsStore*){}));
    Dispatcher::get().addStore("AlbumsStore", QSharedPointer<AlbumsStore>(&AlbumsStore::get(), [](AlbumsStore*){}));
    Dispatcher::get().addStore("AlbumStore", QSharedPointer<AlbumStore>(&AlbumStore::get(), [](AlbumStore*){}));
    /// \warning Dont change the middlewares registration order
    Dispatcher::get().addMiddleware("SessionFactory", QSharedPointer<SessionFactory>(m_SessionFactory, [](SessionFactory*){}));
    Dispatcher::get().addMiddleware("LinkMiddleware", QSharedPointer<LinkMiddleware>(m_LinkMiddleware, [](LinkMiddleware*){}));
    Dispatcher::get().addMiddleware("ServerNetworkMiddleware",
                            QSharedPointer<NetworkAccessMiddleware>(m_NetworkAccessMiddleware, [](NetworkAccessMiddleware*){}));
    Dispatcher::get().addMiddleware("ClientNetworkMiddleware",
                            QSharedPointer<ClientNetworkAccessMiddleware>(m_ClientNetworkMiddleware, [](ClientNetworkAccessMiddleware*){}));

    connect(&RootStore::get(), &RootStore::sessionCreated, this, &Core::onSessionCreated);
    connect(&ClientStore::get(), &ClientStore::connectedToAlbum, this, &Core::onConnectedToAlbum);
}

void Core::onSessionCreated() {
    Dispatcher::get().removeStore("ClientStore");
    Dispatcher::get().removeMiddleware("ClientNetworkMiddleware");
    disconnect(&RootStore::get(), &RootStore::sessionCreated, this, &Core::onSessionCreated);
}

void Core::onConnectedToAlbum() {
    Dispatcher::get().removeStore("AlbumStore");
    Dispatcher::get().removeStore("AlbumsStore");
    Dispatcher::get().removeStore("SessionsStore");
    Dispatcher::get().removeMiddleware("ServerNetworkMiddleware");
    Dispatcher::get().removeMiddleware("LinkMiddleware");
    Dispatcher::get().removeMiddleware("SessionFactory");
    disconnect(&ClientStore::get(), &ClientStore::connectedToAlbum, this, &Core::onConnectedToAlbum);
}
