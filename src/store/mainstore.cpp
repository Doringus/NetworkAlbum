#include "mainstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"
#include "../imageconverter.h"

#include <QDir>
#include <QtConcurrent>
#include <QFutureWatcher>
#include <QVariant>

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
        case ActionType::OPEN_CONNECT_POPUP: {
            processShowOpenPopup();
            break;
        }
        case ActionType::HIDE_CONNECT_POPUP: {
            processHideOpenPopup();
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
        case ActionType::CONNECT_TO_ALBUM: {
            if(action->hasError()) {
                processShowError(action->getErrorString());
            } else {
                processShowError("");
            }
            break;
        }
        case ActionType::CLIENT_CONNECTED: {
           processSendImages(action->getData<networkMessage_t>());
        }
    }
}

bool MainStore::getShowCreatePopup() {
    return m_ShowCreatePopup;
}

bool MainStore::getShowOpenPopup() {
    return m_ShowOpenPopup;
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

void MainStore::processShowOpenPopup() {
    m_ShowOpenPopup = true;
    emit showOpenPopupChanged();
}

void MainStore::processHideOpenPopup() {
    m_ShowOpenPopup = false;
    emit showOpenPopupChanged();
}

void MainStore::processCreateAlbum(Session session) {
    if(m_Sessions.contains(session)) {
        processShowError("Папка уже используется!");
        return;
    }
    if(m_Sessions.size() == 0) {
        Dispatcher::get().dispatch(new Action(ActionType::START_SERVER));
    }
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

void MainStore::processSendImages(networkMessage_t message) {
    qDebug() << "Starting image sending process" << message.clientLink << message.workerIndex;
    auto it = std::find_if(m_Sessions.begin(), m_Sessions.end(), [=](Session session){
        return session.getLink() == message.clientLink;
    });
    if(it != m_Sessions.end()) {
        qDebug() << "Session found";
        qDebug() << it->getAlbumPath().path();
        QDir albumDir(it->getAlbumPath().toLocalFile());
        QFileInfoList paths = albumDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
        ImageConventer scaler;
        QFuture future = scaler.scaleAndConvertImages(paths, QSize(100, 100));
        QFutureWatcher<QList<QJsonObject>> *watcher = new QFutureWatcher<QList<QJsonObject>>();
        connect(watcher, &QFutureWatcher<QList<QJsonValue>>::finished, [message, future]() mutable {
            QList<QJsonObject> scaledImages = future.result();
            message.data = QVariant::fromValue<QList<QJsonObject>>(scaledImages);
            Dispatcher::get().dispatch(new Action(ActionType::SEND_IMAGES, QVariant::fromValue(message)));
        });
        watcher->setFuture(future);
    }
}

