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
        case ActionType::RECEIVE_MESSAGE: {
            processReceiveMessage(action->getData<networkMessage_t>().clientLink);
            break;
        }
        case ActionType::OPEN_ALBUM: {
            m_CurrentAlbumIndex = action->getData<int>();
            m_Albums.clearNotifications(m_CurrentAlbumIndex);
            break;
        }
        case ActionType::OPEN_RESERVE_ALBUM: {
            m_CurrentAlbumIndex = action->getData<int>();
            m_Albums.clearNotifications(m_CurrentAlbumIndex);
            break;
        }
        case ActionType::RETURN_TO_ALBUMS_PAGE: {
            m_CurrentAlbumIndex = -1;
            break;
        }
        case ActionType::SHOW_SETTINGS_POPUP: {
            setSettingPopupVisibility(true);
            if(m_CurrentAlbumIndex == -1) {
                setShowAlbumSettings(false);
            } else {
                setShowAlbumSettings(true);
            }
            break;
        }
        case ActionType::HIDE_SETTINGS_POPUP: {
            setSettingPopupVisibility(false);
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

bool AlbumsStore::getShowSettingsPopup() {
    return m_ShowSettingsPopup;
}

bool AlbumsStore::getShowAlbumSettings() {
    return m_ShowAlbumSettings;
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

void AlbumsStore::processReceiveMessage(const QString& link) {
    int sessionIndex = SessionsStore::get().getSessionIndex(link);
    if(m_CurrentAlbumIndex != sessionIndex && sessionIndex != -1) {
        m_Albums.addNotification(sessionIndex);
    }
}

void AlbumsStore::setSettingPopupVisibility(bool visible) {
    m_ShowSettingsPopup = visible;
    emit showSettingsPopupChanged();
}

void AlbumsStore::setShowAlbumSettings(bool visible) {
    m_ShowAlbumSettings = visible;
    emit showAlbumSettingsChanged();
}
