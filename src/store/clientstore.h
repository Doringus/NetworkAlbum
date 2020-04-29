#pragma once

#include <QObject>
#include <QUrl>
#include <QHash>

#include "../base/store.h"
#include "../displayfilesystemmodel.h"
#include "../conversationmodel.h"
#include "albumstore.h"

class ClientStore : public AlbumStore {
    Q_OBJECT
public:
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorStringChanged)
    Q_PROPERTY(bool showCreateFolderPopup READ getShowCreateFolderPopup NOTIFY showCreateFolderPopupChanged)
    Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QUrl currentMoveFolder READ getCurrentMoveFolder NOTIFY currentMoveFolderChanged)
    Q_PROPERTY(QString currentMoveFolderName READ getCurrentMoveFolderName NOTIFY currentMoveFolderNameChanged)
    Q_PROPERTY(bool showMovePopup READ getShowMovePopup NOTIFY showMovePopupChanged)
    Q_PROPERTY(bool showRenamePopup READ getShowRenamePopup NOTIFY showRenamePopupChanged)
    Q_PROPERTY(bool showReconnectPopup READ getShowReconnectPopup NOTIFY showReconnectPopupChanged)
public:

    ClientStore(const ClientStore&) = delete;
    ClientStore& operator=(const ClientStore&) = delete;

    static ClientStore& get() {
        static ClientStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

    QString getErrorString();
    bool getShowCreateFolderPopup();
    QString getFileName();
    QUrl getCurrentMoveFolder();
    QString getCurrentMoveFolderName();
    bool getShowMovePopup();
    bool getShowRenamePopup();
    bool getShowReconnectPopup();
signals:
    void errorStringChanged();
    void showCreateFolderPopupChanged();
    void fileNameChanged();
    void currentMoveFolderChanged();
    void currentMoveFolderNameChanged();
    void showMovePopupChanged();
    void showRenamePopupChanged();
    void showReconnectPopupChanged();

    void connectedToAlbum();
private:
    ClientStore();
    void processReceiveImages(const QJsonObject& jsonAlbum);
    void processCreateFolder(QString folderName);
    void processOpenFolder(const QUrl& folderUrl);
    void processShowError(const QString& errorString);
    void setCreateFolderPopupVisibility(bool visible);
    void processAddSelectedUrl(const QUrl& url);
    void processDeselectFile(const QUrl& url);
    void processClearSelectedUrl();
    void processChangeMoveDir(const QUrl& url);
    void processMoveFiles(const QUrl& dest);
    void setMovePopupVisibility(bool visible);
    void setRenamePopupVisibility(bool visible);
    void processRenameFile(const QString& newName);
    void processDeleteFiles();
    void processSyncImages();
    void processSendMessage(const QString& message);
    void processReceiveMessage(const QString& message);
    void processCloseSession();
    void processShowReconnectPopup(bool show);

    void setFileName(const QString& albumName);
    void setCurrentMoveFolderName(const QString& name);
    void saveChanges(const QString& oldPath, const QString& newPath);
private:
    QUrl  m_CurrentMoveFolder;
    QString m_ErrorString = "", m_FileName = "", m_CurrentMoveFolderName = "";
    bool m_ShowCreateFolderPopup = false, m_ShowMovePopup = false, m_ShowRenamePopup = false, m_ShowReconnectPopup = false;
    QList<QUrl> m_SelectedUrls;
    QList<QString> m_CreatedFolders;
    QHash<QString, QString> m_ChangesHistory;
    QDir m_AlbumDir;
};
