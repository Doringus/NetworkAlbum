#include "albumsstore.h"

#include <QDir>

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"
#include "sessionsstore.h"

void AlbumsStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            if(action->getErrorString() == "") {
                processAddAlbum(action->getData<Session>());
            }
            break;
        }
        case ActionType::SHOW_LINK_POPUP: {
            processShowAlbumLinks(action->getData<int>());
            setShowLinkPopupVisibility(true);
            break;
        }
        case ActionType::HIDE_LINK_POPUP: {
            setShowLinkPopupVisibility(false);
            break;
        }
    }
}

bool AlbumsStore::getShowLinkPopup() {
    return m_ShowLinkPopup;
}

QString AlbumsStore::getAlbumGlobalLink() {
    return m_GlobalLink;
}

QString AlbumsStore::getAlbumLocalLink() {
    return m_LocalLink;
}

QAbstractListModel* AlbumsStore::getAlbumsModel() {
    return &m_Albums;
}

void AlbumsStore::processAddAlbum(const Session& session) {
    QDir albumDir(session.getAlbumPath().toLocalFile());
    QFileInfoList files = albumDir.entryInfoList({"*.jpg", "*.png"});
    QUrl titleImageUrl;
    if(files.size() != 0) {
        titleImageUrl = QUrl::fromLocalFile(files.first().filePath());
    }
    m_Albums.add(session.getAlbumPath().fileName(), titleImageUrl);
}

void AlbumsStore::setShowLinkPopupVisibility(bool visible) {
    m_ShowLinkPopup = visible;
    emit showLinkPopupChanged();
}

void AlbumsStore::processShowAlbumLinks(int index) {
    if(index == -1) {
        m_GlobalLink = SessionsStore::get().getCurrentSession().getGlobalLink();
        m_LocalLink = SessionsStore::get().getCurrentSession().getLocalLink();
    } else {
        m_GlobalLink = SessionsStore::get().getSession(index).getGlobalLink();
        m_LocalLink = SessionsStore::get().getSession(index).getLocalLink();
    }
    emit albumGlobalLinkChanged();
    emit albumLocalLinkChanged();
}
