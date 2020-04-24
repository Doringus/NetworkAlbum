#pragma once

#include <QObject>
#include <QUrl>
#include <QHash>

#include "../base/store.h"
#include "../displayfilesystemmodel.h"
#include "../conversationmodel.h"

class ClientStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QUrl albumUrl READ getAlbumUrl NOTIFY albumUrlChanged)
    Q_PROPERTY(QUrl currentFolderUrl READ getCurrentFolderUrl NOTIFY currentFolderUrlChanged)
    Q_PROPERTY(QUrl imageUrl READ getImageUrl NOTIFY imageUrlChanged)
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorStringChanged)
    Q_PROPERTY(bool showCreateFolderPopup READ getShowCreateFolderPopup NOTIFY showCreateFolderPopupChanged)
    Q_PROPERTY(QString folderName READ getFolderName NOTIFY folderNameChanged)
    Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QUrl currentMoveFolder READ getCurrentMoveFolder NOTIFY currentMoveFolderChanged)
    Q_PROPERTY(QString currentMoveFolderName READ getCurrentMoveFolderName NOTIFY currentMoveFolderNameChanged)
    Q_PROPERTY(bool showMovePopup READ getShowMovePopup NOTIFY showMovePopupChanged)
    Q_PROPERTY(bool showRenamePopup READ getShowRenamePopup NOTIFY showRenamePopupChanged)
    Q_PROPERTY(QAbstractListModel* conversationModel READ getConversationModel NOTIFY conversationModelChanged)
public:

    ClientStore(const ClientStore&) = delete;
    ClientStore& operator=(const ClientStore&) = delete;

    static ClientStore& get() {
        static ClientStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

    bool getShowConnectPopup();
    QUrl getAlbumUrl();
    QUrl getCurrentFolderUrl();
    QUrl getImageUrl();
    QString getErrorString();
    QString getFolderName();
    bool getShowCreateFolderPopup();
    QString getFileName();
    QUrl getCurrentMoveFolder();
    QString getCurrentMoveFolderName();
    bool getShowMovePopup();
    bool getShowRenamePopup();
    QAbstractListModel* getConversationModel();
signals:
    void showConnectPopupChanged();
    void albumUrlChanged();
    void currentFolderUrlChanged();
    void imageUrlChanged();
    void errorStringChanged();
    void showCreateFolderPopupChanged();
    void folderNameChanged();
    void fileNameChanged();
    void currentMoveFolderChanged();
    void currentMoveFolderNameChanged();
    void showMovePopupChanged();
    void showRenamePopupChanged();
    void conversationModelChanged();

    void connectedToAlbum();
private:
    ClientStore() = default;
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

    void setFolderName(const QString& folderName);
    void setFileName(const QString& albumName);
    void setCurrentMoveFolderName(const QString& name);
    void saveChanges(const QString& oldPath, const QString& newPath);
private:
    QUrl m_CurrentAlbumUrl, m_CurrentFolderUrl, m_ImageUrl, m_CurrentMoveFolder;
    QString m_ErrorString = "", m_FolderName = "", m_FileName = "", m_CurrentMoveFolderName = "";
    bool m_ShowCreateFolderPopup = false, m_ShowMovePopup = false, m_ShowRenamePopup = false, m_ShowConnectPopup;
    QList<QUrl> m_SelectedUrls;
    QList<QString> m_CreatedFolders;
    QHash<QString, QString> m_ChangesHistory;
    QDir m_AlbumDir;
    ConversationModel m_Conversation;
};
