#include "mainstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"

#include <QDir>

MainStore::MainStore() {
    m_AlbumPageTitle = "#TITLE";
}

void MainStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            if(action->hasError()) {
                processShowError(action->getErrorString());
            } else {
                processShowError("");
                processCreateAlbum(action->getData<Session>());
            }
            break;
        }
        case ActionType::OPEN_CREATION_POPUP: {
            processShowCreatePopup();
            break;
        }
        case ActionType::HIDE_CREATION_POPUP: {
            processHideCreatePopup();
            processShowError("");
            break;
        }
        case ActionType::OPEN_ALBUM: {
            processOpenAlbum(action->getData<int>());
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
            processHideImagePopup();
            break;
        }

    }
}

bool MainStore::getShowCreatePopup() {
    return m_ShowCreatePopup;
}

QAbstractListModel *MainStore::getAlbumsModel() {
    return &m_Albums;
}

QUrl MainStore::getAlbumUrl() {
    return m_CurrentAlbumUrl;
}

QUrl MainStore::getCurrentFolderUrl() {
    return m_CurrentFolderUrl;
}

QString MainStore::getAlbumPageTitle() {
    return m_AlbumPageTitle;
}

bool MainStore::getShowImagePopup() {
    return m_ShowImagePopup;
}

QUrl MainStore::getImageUrl() {
    return m_ImageUrl;
}

QString MainStore::getErrorString() {
    return m_ErrorString;
}

void MainStore::processShowCreatePopup() {
    m_ShowCreatePopup = true;
    emit showCreatePopupChanged();
}

void MainStore::processHideCreatePopup() {
    m_ShowCreatePopup = false;
    emit showCreatePopupChanged();
}

void MainStore::processCreateAlbum(Session session) {
    QDir albumDir(session.getAlbumPath().toLocalFile());
    QFileInfoList files = albumDir.entryInfoList({"*.jpg", "*.png"});
    QUrl titleImageUrl;
    if(files.size() != 0) {
        titleImageUrl = QUrl::fromLocalFile(files.first().filePath());
    }
    m_Albums.add(session.getAlbumPath().fileName(), titleImageUrl);
    emit albumsModelChanged();
    m_Sessions.append(session);
    emit sessionCreated();
}

void MainStore::processOpenAlbum(int index) {
    m_AlbumPageTitle = m_Sessions.at(index).getAlbumPath().fileName();
    m_CurrentAlbumUrl = m_Sessions.at(index).getAlbumPath();
    m_CurrentFolderUrl = m_Sessions.at(index).getAlbumPath();
    emit albumUrlChanged();
    emit currentFolderUrlChanged();
    emit albumPageTitleChanged();
}

void MainStore::processOpenFolder(QUrl folder) {
    m_CurrentFolderUrl = folder;
    m_AlbumPageTitle = folder.fileName();
    emit currentFolderUrlChanged();
    emit albumPageTitleChanged();
}

void MainStore::processOpenImagePopup(QUrl imageUrl) {
    m_ShowImagePopup = true;
    m_ImageUrl = imageUrl;
    emit imageUrlChanged();
    emit showImagePopupChanged();
}

void MainStore::processHideImagePopup() {
    m_ShowImagePopup = false;
    emit showImagePopupChanged();
}

void MainStore::processShowError(QString errorString) {
    m_ErrorString = errorString;
    emit errorStringChanged();
}

