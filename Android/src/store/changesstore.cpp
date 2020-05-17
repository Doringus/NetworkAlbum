#include "changesstore.h"

#include <QStandardPaths>

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"

void ChangesStore::process(const QSharedPointer<Action> &action) {
     switch (action->getType<ActionType>()) {
        case ActionType::RECEIVE_ALBUM_INFO: {
            if(action->getErrorString() == "") {
                processReceiveAlbumInfo(action->getData<QPair<QString, double>>().first);
            }
            break;
        }
        case ActionType::OPEN_FOLDER: {
            processOpenFolder(action->getData<QUrl>());
            break;
        }
         case ActionType::CREATE_FOLDER: {
             processCreateFolder(action->getData<QString>());
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
         case ActionType::CHANGE_MOVE_DIR: {
             processChangeMoveDir(action->getData<QUrl>());
             break;
         }
         case ActionType::MOVE_FILES: {
             processMoveFiles(action->getData<QUrl>());
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
         case ActionType::CLIENT_DISCONNECTED: {
             processShowReconnectPopup(true);
             break;
         }
         case ActionType::HIDE_RECONNECT_POPUP: {
             processShowReconnectPopup(false);
             break;
         }
         case ActionType::CLEAR_AND_SELECT_FILES: {
             processClearSelectedUrl();
             processAddSelectedUrl(action->getData<QUrl>());
             break;
         }
     }
}

QString ChangesStore::getErrorString() {
    return m_ErrorString;
}

bool ChangesStore::getShowCreateFolderPopup() {
    return m_ShowCreateFolderPopup;
}

QUrl ChangesStore::getCurrentMoveFolder() {
    return m_CurrentMoveFolder;
}

QString ChangesStore::getCurrentMoveFolderName() {
    return m_CurrentMoveFolderName;
}

bool ChangesStore::getShowReconnectPopup() {
    return m_ShowReconnectPopup;
}

bool ChangesStore::getShowRenamePopup() {
    return m_ShowRenamePopup;
}

QString ChangesStore::getFileName() {
    return m_FileName;
}

void ChangesStore::processReceiveAlbumInfo(const QString &albumName) {
    m_AlbumDir.setPath(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first() + "/" + albumName);
    m_CurrentFolderUrl = QUrl::fromLocalFile(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first() + "/" + albumName);
    processChangeMoveDir(m_CurrentFolderUrl);
    emit currentMoveFolderChanged();
}

void ChangesStore::processCreateFolder(QString folderName) {
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

void ChangesStore::processShowError(const QString &errorString) {
    m_ErrorString = errorString;
    emit errorStringChanged();
}

void ChangesStore::processAddSelectedUrl(const QUrl &url) {
    m_SelectedUrls.append(url);
    if(m_SelectedUrls.size() > 1) {
        setFileName(QString::number(m_SelectedUrls.size()) + " " + getEnding(m_SelectedUrls.size()));
    } else {
        setFileName(url.fileName());
    }
}

void ChangesStore::processDeselectFile(const QUrl &url) {
    m_SelectedUrls.removeOne(url);
    if(m_SelectedUrls.size() == 0) {
        setFileName("");
    } else if(m_SelectedUrls.size() == 1) {
        setFileName(m_SelectedUrls.first().fileName());
    } else {
        setFileName(QString::number(m_SelectedUrls.size()) + " " + getEnding(m_SelectedUrls.size()));
    }
}

void ChangesStore::processClearSelectedUrl() {
    m_SelectedUrls.clear();
    setFileName("");
}

void ChangesStore::processChangeMoveDir(const QUrl &url) {
    m_CurrentMoveFolder = url;
    setCurrentMoveFolderName(url.fileName());
    emit currentMoveFolderChanged();
}

void ChangesStore::processMoveFiles(const QUrl &dest) {
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
    emit filesMoved();
}

void ChangesStore::processRenameFile(const QString &newName) {
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

void ChangesStore::processDeleteFiles() {
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

void ChangesStore::processSyncImages() {
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

void ChangesStore::processShowReconnectPopup(bool show) {
    m_ShowReconnectPopup = show;
    emit showReconnectPopupChanged();
}

void ChangesStore::processOpenFolder(const QUrl &url) {
    m_CurrentFolderUrl = url;
}

void ChangesStore::saveChanges(const QString &oldPath, const QString &newPath) {
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

void ChangesStore::setCreateFolderPopupVisibility(bool visible) {
    m_ShowCreateFolderPopup = visible;
    emit showCreateFolderPopupChanged();
}

void ChangesStore::setRenamePopupVisibility(bool visible) {
    m_ShowRenamePopup = visible;
    emit showRenamePopupChanged();
}

void ChangesStore::setFileName(const QString &fileName) {
    m_FileName = fileName;
    emit fileNameChanged();
}

void ChangesStore::setCurrentMoveFolderName(const QString &folderName) {
    m_CurrentMoveFolderName = folderName;
    emit currentMoveFolderNameChanged();
}

QString ChangesStore::getEnding(int num) {
    QString files = "Файлов";

    if(num != 11 && num != 111 && num != 1111) {
        switch (num % 10) {
            case 1: files = "Файл"; break;
            case 2: files = "Файла";break;
            case 3: files = "Файла";break;
            case 4: files = "Файла";break;
            default: files = "Файлов";break;
        }
    } else {
        files = "Файлов";
    }
    return files;
}

