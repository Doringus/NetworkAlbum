#include "albumstore.h"

#include <QDesktopServices>

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
        case ActionType::OPEN_RESERVE_ALBUM: {
            processOpenReserveAlbum();
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
        case ActionType::OPEN_IN_EXPLORER: {
            processOpenInExplorer();
            break;
        }
        case ActionType::SHOW_CHAT: {
            setChatVisibility(true);
            break;
        }
        case ActionType::HIDE_CHAT: {
            setChatVisibility(false);
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

QString AlbumStore::albumReserveFolder() {
    return m_AlbumReserveFolder;
}

bool AlbumStore::getShowChat() {
    return m_ShowChat;
}

void AlbumStore::processOpenAlbum() {
    QUrl albumPath = SessionsStore::get().getCurrentSession().getAlbumPath();
    m_Conversation = SessionsStore::get().getCurrentSession().getConversation();
    m_AlbumReserveFolder = SessionsStore::get().getCurrentSession().getReserveFolder();
    m_AlbumPageTitle = albumPath.fileName();
    m_CurrentAlbumUrl = albumPath;
    m_CurrentFolderUrl = albumPath;
    emit albumUrlChanged();
    emit currentFolderUrlChanged();
    emit albumPageTitleChanged();
    emit conversationModelChanged();
    emit albumReserveFolderChanged();
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

void AlbumStore::processOpenReserveAlbum() {
    QUrl albumPath = SessionsStore::get().getCurrentSession().getAlbumPath();
    QUrl reserve = SessionsStore::get().getCurrentSession().getAlbumReservePath();
    m_Conversation = SessionsStore::get().getCurrentSession().getConversation();
    m_AlbumReserveFolder = reserve.toLocalFile();
    m_AlbumPageTitle = albumPath.fileName();
    m_CurrentAlbumUrl = reserve;
    m_CurrentFolderUrl = reserve;
    emit albumUrlChanged();
    emit currentFolderUrlChanged();
    emit albumPageTitleChanged();
    emit conversationModelChanged();
    emit albumReserveFolderChanged();
}

void AlbumStore::processOpenInExplorer(){
    QDesktopServices::openUrl(m_CurrentFolderUrl);
}

void AlbumStore::setImagePopupVisibility(bool visible) {
    m_ShowImagePopup = visible;
    emit showImagePopupChanged();
}

void AlbumStore::setChatVisibility(bool visible) {
    m_ShowChat = visible;
    emit showChatChanged();
}
