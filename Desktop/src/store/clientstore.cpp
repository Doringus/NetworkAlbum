#include "clientstore.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QImage>
#include <QDir>

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"

void ClientStore::process(const QSharedPointer<Action> &action) {
    AlbumStore::process(action);
    switch (action->getType<ActionType>()) {
        case ActionType::IMAGES_RECEIVED: {
            if(action->getErrorString() == "") {
                processReceiveImages(action->getData<QJsonObject>());
            } else {
                processShowError(action->getErrorString());
            }

            break;
        }
        case ActionType::CREATE_FOLDER: {
            processCreateFolder(action->getData<QString>());
            break;
        }
        case ActionType::OPEN_FOLDER: {
            processOpenFolder(action->getData<QUrl>());
            break;
        }
        case ActionType::SHOW_CREATE_FOLDER_POPUP: {
            setCreateFolderPopupVisibility(true);
            break;
        }
        case ActionType::HIDE_CREATE_FOLDER_POPUP: {
            setCreateFolderPopupVisibility(false);
            processShowError("");
            break;
        }
        case ActionType::SELECT_FILE: {
            processAddSelectedUrl(action->getData<QUrl>());
            break;
        }
        case ActionType::DESELECT_FILES: {
            processClearSelectedUrl();
            break;
        }
        case ActionType::DESELECT_FILE: {
            processDeselectFile(action->getData<QUrl>());
            break;
        }
        case ActionType::CLEAR_AND_SELECT_FILES: {
            processClearSelectedUrl();
            processAddSelectedUrl(action->getData<QUrl>());
            break;
        }
        case ActionType::CHANGE_MOVE_DIR: {
            processChangeMoveDir(action->getData<QUrl>());
            break;
        }
        case ActionType::MOVE_FILES: {
            processMoveFiles(action->getData<QUrl>());
            break;
        }
        case ActionType::SHOW_MOVE_POPUP: {
            setMovePopupVisibility(true);
            break;
        }
        case ActionType::HIDE_MOVE_POPUP: {
            setMovePopupVisibility(false);
            processShowError("");
            break;
        }
        case ActionType::SHOW_RENAME_POPUP: {
            if(m_SelectedUrls.size() == 1) {
                setRenamePopupVisibility(true);
            }
            break;
        }
        case ActionType::HIDE_RENAME_POPUP: {
            setRenamePopupVisibility(false);
            processShowError("");
            break;
        }
        case ActionType::RENAME_FILE: {
            processRenameFile(action->getData<QString>());
            break;
        }
        case ActionType::DELETE_FILES: {
            processDeleteFiles();
            break;
        }
        case ActionType::SYNC_IMAGES: {
            processSyncImages();
            break;
        }
        case ActionType::BEGIN_SEND_MESSAGE: {
            processSendMessage(action->getData<QString>());
            break;
        }
        case ActionType::RECEIVE_MESSAGE: {
            processReceiveMessage(action->getData<QString>());
            break;
        }
        case ActionType::CLIENT_DISCONNECTED: {
            processShowReconnectPopup(true);
            break;
        }
        case ActionType::CLIENT_CONNECTED: {
            if(action->getErrorString() != "") {
                processShowError(action->getErrorString());
            }
            break;
        }
        case ActionType::HIDE_RECONNECT_POPUP: {
            processShowReconnectPopup(false);
            break;
        }
        case ActionType::RECEIVE_ALBUM_INFO: {
            processReceiveAlbumInfo(action->getData<QPair<QString, double>>().first, action->getData<QPair<QString, double>>().second);
            break;
        }
    }
}


QString ClientStore::getErrorString() {
    return m_ErrorString;
}

bool ClientStore::getShowCreateFolderPopup() {
    return m_ShowCreateFolderPopup;
}

QString ClientStore::getFileName() {
    return m_FileName;
}

QUrl ClientStore::getCurrentMoveFolder() {
    return m_CurrentMoveFolder;
}

QString ClientStore::getCurrentMoveFolderName() {
    return m_CurrentMoveFolderName;
}

bool ClientStore::getShowMovePopup() {
    return m_ShowMovePopup;
}

bool ClientStore::getShowRenamePopup() {
    return m_ShowRenamePopup;
}

bool ClientStore::getShowReconnectPopup() {
    return m_ShowReconnectPopup;
}

bool ClientStore::getShowConnectButton() {
    return m_ConnectButtonVisibility;
}

QString ClientStore::getAlbumName() {
    return m_AlbumName;
}

double ClientStore::getAlbumSize() {
    return m_AlbumSize;
}

ClientStore::ClientStore() {
    m_Conversation = new ConversationModel(this);
}

void ClientStore::processReceiveImages(const QJsonObject& jsonAlbum) {
    QJsonArray jsonImages = jsonAlbum.value("MessageValue").toArray();
    QString albumName = m_AlbumName;
    QString folderPath = QDir::currentPath() + "/" + albumName;
    m_AlbumDir.setPath(QDir::currentPath() + "/" + albumName);
    QDir dir(folderPath);
    if(dir.exists()) {
        dir.removeRecursively();
    }
    dir.mkdir(folderPath);
    for(int i = 0; i < jsonImages.size(); ++i) {
        QJsonObject imageObject = jsonImages.at(i).toObject();
        auto encoded = imageObject.value("Data").toString().toLatin1();
        QImage image;
        image.loadFromData(QByteArray::fromBase64(encoded), "JPG");
        image.save(albumName + "/" + imageObject.value("Name").toString() + ".jpg", "JPG");
    }
    setAlbumPageTitle(albumName);
    setCurrentMoveFolderName(albumName);
    setAlbumUrl(QUrl::fromLocalFile(dir.absolutePath()));;
    setCurrentFolderUrl(QUrl::fromLocalFile(dir.absolutePath()));
    processChangeMoveDir(getAlbumUrl());
    emit connectedToAlbum();
}

void ClientStore::processCreateFolder(QString folderName) {
    if(folderName == "") {
        processShowError("Некорректное имя папки");
        return;
    }
    folderName = folderName.trimmed();
    QString folderPath = getCurrentFolderUrl().toString(QUrl::PreferLocalFile) + "/" + folderName;
    QDir dir(folderPath);
    if(dir.exists()) {
        processShowError("Папка с таким именем уже существует");
        return;
    }
    if(!dir.mkdir(folderPath)) {
        processShowError("Системе не удалось создать папку");
        return;
    }
    m_CreatedFolders.append(m_AlbumDir.relativeFilePath(folderPath));
    setCreateFolderPopupVisibility(false);
}

void ClientStore::processOpenFolder(const QUrl& folderUrl) {
    processClearSelectedUrl();
}

void ClientStore::processShowError(const QString& errorString) {
    m_ErrorString = errorString;
    emit errorStringChanged();
}

void ClientStore::setCreateFolderPopupVisibility(bool visible) {
    m_ShowCreateFolderPopup = visible;
    emit showCreateFolderPopupChanged();
}

void ClientStore::setFileName(const QString& albumName) {
    m_FileName = albumName;
    emit fileNameChanged();
}

void ClientStore::setCurrentMoveFolderName(const QString& name) {
    m_CurrentMoveFolderName = name;
    emit currentMoveFolderNameChanged();
}

void ClientStore::saveChanges(const QString& oldPath, const QString& newPath) {
    QString oldValue = m_ChangesHistory.value(oldPath, "");
    if(newPath == oldValue) {
        m_ChangesHistory.remove(oldPath);
        return;
    }
    if(oldValue != "") {
        m_ChangesHistory.remove(oldPath);
        m_ChangesHistory.insert(newPath, oldValue);
    } else {
        m_ChangesHistory.insert(newPath, oldPath);
    }
}

void ClientStore::processAddSelectedUrl(const QUrl& url) {
    m_SelectedUrls.append(url);
    if(m_SelectedUrls.size() > 1) {
        QString files = "Файлов";

        if(m_SelectedUrls.size() != 11 && m_SelectedUrls.size() != 111 && m_SelectedUrls.size() != 1111) {
            switch (m_SelectedUrls.size() % 10) {
                case 1: files = "Файл"; break;
                case 2: files = "Файла";break;
                case 3: files = "Файла";break;
                case 4: files = "Файла";break;
                default: files = "Файлов";break;
            }
        } else {
            files = "Файлов";
        }
        setFileName(QString::number(m_SelectedUrls.size()) + " " + files);
    } else {
        setFileName(url.fileName());
    }
}

void ClientStore::processDeselectFile(const QUrl& url) {
    m_SelectedUrls.removeOne(url);
    if(m_SelectedUrls.size() == 0) {
        setFileName("");
    } else if(m_SelectedUrls.size() == 1) {
        setFileName(m_SelectedUrls.first().fileName());
    } else {
        setFileName(QString::number(m_SelectedUrls.size()) + " Файлов");
    }
}

void ClientStore::processClearSelectedUrl() {
    m_SelectedUrls.clear();
    setFileName("");
}

void ClientStore::processChangeMoveDir(const QUrl& url) {
    m_CurrentMoveFolder = url;
    setCurrentMoveFolderName(url.fileName());
    emit currentMoveFolderChanged();
}

void ClientStore::processMoveFiles(const QUrl& dest) {
    if(m_SelectedUrls.contains(dest)) {
        processShowError("Не удалось перенести файлы");
        return;
    }
    foreach(QUrl url, m_SelectedUrls) {
        QDir dir;
        if(!dir.rename(url.toLocalFile(), dest.toLocalFile() + "/" + url.fileName())) {
            processShowError("Не удалось перенести файлы");
            return;
        }
        saveChanges(m_AlbumDir.relativeFilePath(url.toLocalFile()), m_AlbumDir.relativeFilePath(dest.toLocalFile() + "/" + url.fileName()));
    }
    processClearSelectedUrl();
    setMovePopupVisibility(false);
}

void ClientStore::setMovePopupVisibility(bool visible) {
    m_ShowMovePopup = visible;
    emit showMovePopupChanged();
}

void ClientStore::setRenamePopupVisibility(bool visible) {
    m_ShowRenamePopup = visible;
    emit showRenamePopupChanged();
}

void ClientStore::processRenameFile(const QString& newName) {
    QFileInfo fileInfo(m_SelectedUrls.first().toLocalFile());
    QFile file(m_SelectedUrls.first().toLocalFile());
    if(!file.rename(fileInfo.absolutePath() + "/" + newName)) {
        processShowError("Такое имя уже используется");
        return;
    }
    processClearSelectedUrl();
    saveChanges(m_AlbumDir.relativeFilePath(fileInfo.absoluteFilePath()),
                m_AlbumDir.relativeFilePath(fileInfo.absolutePath() + "/" + newName));
    setRenamePopupVisibility(false);
}

void ClientStore::processDeleteFiles() {
    foreach(QUrl url, m_SelectedUrls) {
        QString localPath = url.toLocalFile();
        QFileInfo info(localPath);
        if(info.isDir()) {
            QDir dir(localPath);
            if(dir.isEmpty()) {
                dir.removeRecursively();
            }
        }
    }
}

void ClientStore::processSyncImages() {
    if(m_ChangesHistory.empty()) {
        return;
    }
    QList<QPair<QString, QString>> changes;
    QHash<QString, QString>::const_iterator it = m_ChangesHistory.constBegin();
    while (it != m_ChangesHistory.constEnd()) {
        changes.append({it.key(), it.value()});
        ++it;
    }
    m_ChangesHistory.clear();
    Dispatcher::get().dispatch(new Action(ActionType::SEND_SYNC_DATA,
                                          QVariant::fromValue<QList<QPair<QString, QString>>>(changes)));
}

void ClientStore::processSendMessage(const QString &message) {
    m_Conversation->add(message, true);
    Dispatcher::get().dispatch(new Action(ActionType::SEND_MESSAGE, message.trimmed()));
}

void ClientStore::processReceiveMessage(const QString &message) {
    m_Conversation->add(message, false);
}

void ClientStore::processShowReconnectPopup(bool show) {
    m_ShowReconnectPopup = show;
    emit showReconnectPopupChanged();
}

void ClientStore::processReceiveAlbumInfo(QString albumName, double albumSize) {
    m_AlbumName = albumName;
    m_AlbumSize = albumSize;
    m_ConnectButtonVisibility = true;
    emit albumNameChanged();
    emit albumSizeChanged();
    emit showConnectButtonChanged();
}
