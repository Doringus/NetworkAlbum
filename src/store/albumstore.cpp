#include "albumstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"
#include "sessionsstore.h"

void AlbumStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::OPEN_ALBUM: {
            processOpenAlbum();
            break;
        }
        case ActionType::OPEN_FOLDER: {
            processOpenFolder(action->getData<QUrl>());
            break;
        }
        case ActionType::OPEN_IMAGE_POPUP: {
            processOpenImagePopup(action->getData<QUrl>());
            break;
        }
        case ActionType::HIDE_IMAGE_POPUP: {
            setImagePopupVisibility(false);
            break;
        }
    }
}

QUrl AlbumStore::getAlbumUrl() {
    return m_CurrentAlbumUrl;
}

QUrl AlbumStore::getCurrentFolderUrl() {
    return m_CurrentFolderUrl;
}

QUrl AlbumStore::getImageUrl() {
    return m_ImageUrl;
}

QString AlbumStore::getAlbumPageTitle() {
    return m_AlbumPageTitle;
}

bool AlbumStore::getShowImagePopup() {
    return m_ShowImagePopup;
}

QAbstractListModel* AlbumStore::getConversationModel() {
    return m_Conversation;
}

void AlbumStore::processOpenAlbum() {
    QUrl albumPath = SessionsStore::get().getCurrentSession().getAlbumPath();
    m_Conversation = SessionsStore::get().getCurrentSession().getConversation();
    m_AlbumPageTitle = albumPath.fileName();
    m_CurrentAlbumUrl = albumPath;
    m_CurrentFolderUrl = albumPath;
    emit albumUrlChanged();
    emit currentFolderUrlChanged();
    emit albumPageTitleChanged();
    emit conversationModelChanged();
}

void AlbumStore::processOpenFolder(const QUrl& folder) {
    m_CurrentFolderUrl = folder;
    m_AlbumPageTitle = folder.fileName();
    emit currentFolderUrlChanged();
    emit albumPageTitleChanged();
}

void AlbumStore::processOpenImagePopup(const QUrl& imageUrl) {
    m_ImageUrl = imageUrl;
    setImagePopupVisibility(true);
    emit imageUrlChanged();
}

void AlbumStore::setImagePopupVisibility(bool visible) {
    m_ShowImagePopup = visible;
    emit showImagePopupChanged();
}
