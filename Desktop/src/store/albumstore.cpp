#include "albumstore.h"

#include <QDesktopServices>

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"
#include "sessionsstore.h"

void AlbumStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
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

bool AlbumStore::getShowChat() {
    return m_ShowChat;
}

void AlbumStore::setAlbumUrl(const QUrl &url) {
    m_CurrentAlbumUrl = url;
    emit albumUrlChanged();
}

void AlbumStore::setCurrentFolderUrl(const QUrl &url) {
    m_CurrentFolderUrl = url;
    emit currentFolderUrlChanged();
}

void AlbumStore::setImageUrl(const QUrl &url) {
    m_ImageUrl = url;
    emit imageUrlChanged();
}

void AlbumStore::setAlbumPageTitle(const QString &title) {
    m_AlbumPageTitle = title;
    emit albumPageTitleChanged();
}

void AlbumStore::setShowImagePopupVisibility(bool visible) {
    m_ShowImagePopup = visible;
    emit showImagePopupChanged();
}


void AlbumStore::processOpenFolder(const QUrl& folder) {
    setCurrentFolderUrl(folder);
    setAlbumPageTitle(folder.fileName());
}

void AlbumStore::processOpenImagePopup(const QUrl& imageUrl) {
    setImageUrl(imageUrl);
    setImagePopupVisibility(true);
    emit imageUrlChanged();
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
