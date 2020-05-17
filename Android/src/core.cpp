#include "core.h"

#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>

#include "action/actionprovider.h"
#include "store/albuminfostore.h"
#include "store/albumstore.h"
#include "store/changesstore.h"
#include "store/conversationstore.h"
#include "base/dispatcher.h"
#include "middleware/clientnetworkaccessmiddleware.h"

Core::Core(QObject *parent) : QObject(parent) {
    qRegisterMetaType<qintptr>("qintptr");
    qRegisterMetaType<bool>("bool");
    QFontDatabase font;
    m_ClientNetworkMiddleware = new ClientNetworkAccessMiddleware(this);
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
    qmlRegisterSingletonType<AlbumInfoStore>("NetworkAlbum", 1, 0, "AlbumInfoStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&AlbumInfoStore::get(), QQmlEngine::CppOwnership);
        return &AlbumInfoStore::get();
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
    qmlRegisterSingletonType<ChangesStore>("NetworkAlbum", 1, 0, "ChangesStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&ChangesStore::get(), QQmlEngine::CppOwnership);
        return &ChangesStore::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    qmlRegisterSingletonType<ConversationStore>("NetworkAlbum", 1, 0, "ConversationStore",
                                             [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
        QQmlEngine::setObjectOwnership(&ConversationStore::get(), QQmlEngine::CppOwnership);
        return &ConversationStore::get();
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
    });
    Dispatcher::get().addStore(QSharedPointer<AlbumInfoStore>(&AlbumInfoStore::get(), [](AlbumInfoStore*){}));
    Dispatcher::get().addStore(QSharedPointer<AlbumStore>(&AlbumStore::get(), [](AlbumStore*){}));
    Dispatcher::get().addStore(QSharedPointer<ChangesStore>(&ChangesStore::get(), [](ChangesStore*){}));
    Dispatcher::get().addStore(QSharedPointer<ConversationStore>(&ConversationStore::get(), [](ConversationStore*){}));
    Dispatcher::get().addMiddleware(QSharedPointer<ClientNetworkAccessMiddleware>(m_ClientNetworkMiddleware, [](ClientNetworkAccessMiddleware*){}));
}

void Core::onSessionCreated() {

}

void Core::onConnectedToAlbum() {

}
