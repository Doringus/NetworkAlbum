#include "albumstore.h"

#include <QDesktopServices>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QImage>
#include <QStandardPaths>

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"

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
        case ActionType::IMAGES_RECEIVED: {
            if(action->getErrorString() == "") {
                processReceiveImages(action->getData<QJsonObject>());
            }
            break;
        }
        case ActionType::RECEIVE_ALBUM_INFO: {
            if(action->getErrorString() == "") {
                processSetAlbumName(action->getData<QPair<QString, double>>().first);
            }
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

void AlbumStore::processReceiveImages(const QJsonObject &images) {
    QJsonArray jsonImages = images.value("MessageValue").toArray();
    QString folderPath = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first() + "/" + m_AlbumName;
    QDir dir(folderPath);
    if(dir.exists()) {
        dir.removeRecursively();
    }
    qDebug() << "Album dir" << folderPath;
    if(!dir.mkdir(folderPath)) {
        qDebug() << "Failed to create album dir";
    }
    for(int i = 0; i < jsonImages.size(); ++i) {
        QJsonObject imageObject = jsonImages.at(i).toObject();
        auto encoded = imageObject.value("Data").toString().toLatin1();
        QImage image;
        image.loadFromData(QByteArray::fromBase64(encoded), "JPG");
        image.save(folderPath + "/" + imageObject.value("Name").toString() + ".jpg", "JPG");
    }
    setAlbumPageTitle(m_AlbumName);
    setAlbumUrl(QUrl::fromLocalFile(dir.absolutePath()));;
    setCurrentFolderUrl(QUrl::fromLocalFile(dir.absolutePath()));
}

void AlbumStore::processSetAlbumName(const QString &albumName) {
    m_AlbumName = albumName;
}

void AlbumStore::setImagePopupVisibility(bool visible) {
    m_ShowImagePopup = visible;
    emit showImagePopupChanged();
}
