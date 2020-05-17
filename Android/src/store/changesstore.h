#pragma once

#include <QObject>
#include <QUrl>
#include <QDir>

#include "../base/store.h"

class ChangesStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorStringChanged)
    Q_PROPERTY(bool showCreateFolderPopup READ getShowCreateFolderPopup NOTIFY showCreateFolderPopupChanged)
    Q_PROPERTY(QUrl currentMoveFolder READ getCurrentMoveFolder NOTIFY currentMoveFolderChanged)
    Q_PROPERTY(QString currentMoveFolderName READ getCurrentMoveFolderName NOTIFY currentMoveFolderNameChanged)
    Q_PROPERTY(bool showReconnectPopup READ getShowReconnectPopup NOTIFY showReconnectPopupChanged)
    Q_PROPERTY(bool showRenamePopup READ getShowRenamePopup NOTIFY showRenamePopupChanged)
    Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged)
public:
    ChangesStore(const ChangesStore&) = delete;
    ChangesStore& operator=(const ChangesStore&) = delete;

    static ChangesStore& get() {
        static ChangesStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

    QString getErrorString();
    bool getShowCreateFolderPopup();
    QUrl getCurrentMoveFolder();
    QString getCurrentMoveFolderName();
    bool getShowReconnectPopup();
    bool getShowRenamePopup();
    QString getFileName();

signals:
    void errorStringChanged();
    void showCreateFolderPopupChanged();
    void currentMoveFolderChanged();
    void currentMoveFolderNameChanged();
    void showReconnectPopupChanged();
    void showRenamePopupChanged();
    void fileNameChanged();

    void filesMoved();
private:
    ChangesStore() = default;
    void processReceiveAlbumInfo(const QString& albumName);
    void processCreateFolder(QString folderName);
    void processShowError(const QString& errorString);
    void processAddSelectedUrl(const QUrl& url);
    void processDeselectFile(const QUrl& url);
    void processClearSelectedUrl();
    void processChangeMoveDir(const QUrl& url);
    void processMoveFiles(const QUrl& dest);
    void processRenameFile(const QString& newName);
    void processDeleteFiles();
    void processSyncImages();
    void processShowReconnectPopup(bool show);
    void processOpenFolder(const QUrl& url);

    void saveChanges(const QString& oldPath, const QString& newPath);
    void setCreateFolderPopupVisibility(bool visible);
    void setRenamePopupVisibility(bool visible);
    void setFileName(const QString& fileName);
    void setCurrentMoveFolderName(const QString& folderName);
    QString getEnding(int num);
private:
    QString m_ErrorString, m_CurrentMoveFolderName, m_FileName;
    QUrl m_CurrentMoveFolder, m_CurrentFolderUrl;
    bool m_ShowCreateFolderPopup, m_ShowReconnectPopup, m_ShowRenamePopup;
    QHash<QString, QString> m_ChangesHistory;
    QDir m_AlbumDir;
    QList<QUrl> m_SelectedUrls;
};

