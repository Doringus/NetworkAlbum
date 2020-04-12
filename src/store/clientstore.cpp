#include "clientstore.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QImage>
#include <QDir>

#include "../base/action.h"
#include "../action/actiontypes.h"

void ClientStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::IMAGES_RECIEVED: {
            processRecieveImages(action->getData<QJsonObject>());
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
            setMovePopupVisibility(false);
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
    }
}

QUrl ClientStore::getAlbumUrl() {
    return m_CurrentAlbumUrl;
}

QUrl ClientStore::getCurrentFolderUrl() {
    return m_CurrentFolderUrl;
}

QUrl ClientStore::getImageUrl() {
    return m_ImageUrl;
}

QString ClientStore::getErrorString() {
    return m_ErrorString;
}

QString ClientStore::getFolderName() {
    return m_FolderName;
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

void ClientStore::processRecieveImages(QJsonObject jsonAlbum) {
    QJsonArray jsonImages = jsonAlbum.value("Images").toArray();
    QString albumName = "TEST";
    QString folderPath = QDir::currentPath() + "/" + albumName;
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
    setFolderName(albumName);
    setCurrentMoveFolderName(albumName);
    m_CurrentAlbumUrl = QUrl::fromLocalFile(dir.absolutePath());
    m_CurrentFolderUrl = m_CurrentAlbumUrl;
    processChangeMoveDir(m_CurrentAlbumUrl);
    emit albumUrlChanged();
    emit currentFolderUrlChanged();
}

void ClientStore::processCreateFolder(QString folderName) {
    if(folderName == "") {
        processShowError("Некорректное имя папки");
        return;
    }
    folderName = folderName.trimmed();
    QString folderPath = m_CurrentFolderUrl.toString(QUrl::PreferLocalFile) + "/" + folderName;
    QDir dir(folderPath);
    if(dir.exists()) {
        processShowError("Папка с таким именем уже существует");
        return;
    }
    if(!dir.mkdir(folderPath)) {
        processShowError("Системе не удалось создать папку");
        return;
    }
    setCreateFolderPopupVisibility(false);
}

void ClientStore::processOpenFolder(QUrl folderUrl) {
    m_CurrentFolderUrl = folderUrl;
    setFolderName(folderUrl.fileName());
    processClearSelectedUrl();
    emit currentFolderUrlChanged();
}

void ClientStore::processShowError(QString errorString) {
    m_ErrorString = errorString;
    emit errorStringChanged();
}

void ClientStore::setCreateFolderPopupVisibility(bool visible) {
    m_ShowCreateFolderPopup = visible;
    emit showCreateFolderPopupChanged();
}

void ClientStore::setFolderName(QString folderName) {
    m_FolderName = folderName;
    emit folderNameChanged();
}

void ClientStore::setFileName(QString albumName) {
    m_FileName = albumName;
    emit fileNameChanged();
}

void ClientStore::setCurrentMoveFolderName(QString name) {
    m_CurrentMoveFolderName = name;
    emit currentMoveFolderNameChanged();
}

void ClientStore::processAddSelectedUrl(QUrl url) {
    m_SelectedUrls.append(url);
    if(m_SelectedUrls.size() > 1) {
        setFileName(QString::number(m_SelectedUrls.size()) + " Файлов");
    } else {
        setFileName(url.fileName());
    }
}

void ClientStore::processDeselectFile(QUrl url) {
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

void ClientStore::processChangeMoveDir(QUrl url) {
    m_CurrentMoveFolder = url;
    setCurrentMoveFolderName(url.fileName());
    emit currentMoveFolderChanged();
}

void ClientStore::processMoveFiles(QUrl dest) {
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

void ClientStore::processRenameFile(QString newName) {
    QFileInfo fileInfo(m_SelectedUrls.first().toLocalFile());
    QFile file(m_SelectedUrls.first().toLocalFile());
    if(!file.rename(fileInfo.absolutePath() + "/" + newName)) {
        processShowError("Такое имя уже используется");
        return;
    }
    processClearSelectedUrl();
    processAddSelectedUrl(QUrl::fromLocalFile(fileInfo.absolutePath() + "/" + newName));
    setRenamePopupVisibility(false);
}

void ClientStore::processDeleteFiles() {
    foreach(QUrl url, m_SelectedUrls) {
        QString localPath = url.toLocalFile();
        QFileInfo info(localPath);
        if(info.isDir()) {
            QDir dir(localPath);
            dir.removeRecursively();
        } else {
            QFile file;
            file.remove(localPath);
        }
    }
}

