#pragma once

#include <QObject>
#include <QUrl>

#include "../base/store.h"
#include "../displayfilesystemmodel.h"

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
public:

    ClientStore(const ClientStore&) = delete;
    ClientStore& operator=(const ClientStore&) = delete;

    static ClientStore& get() {
        static ClientStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

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
signals:
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
private:
    ClientStore() = default;
    void processRecieveImages(QJsonObject jsonAlbum);
    void processCreateFolder(QString folderName);
    void processOpenFolder(QUrl folderUrl);
    void processShowError(QString errorString);
    void setCreateFolderPopupVisibility(bool visible);
    void processAddSelectedUrl(QUrl url);
    void processDeselectFile(QUrl url);
    void processClearSelectedUrl();
    void processChangeMoveDir(QUrl url);
    void processMoveFiles(QUrl dest);
    void setMovePopupVisibility(bool visible);
    void setRenamePopupVisibility(bool visible);
    void processRenameFile(QString newName);
    void processDeleteFiles();

    void setFolderName(QString folderName);
    void setFileName(QString albumName);
    void setCurrentMoveFolderName(QString name);
private:
    QUrl m_CurrentAlbumUrl, m_CurrentFolderUrl, m_ImageUrl, m_CurrentMoveFolder;
    QString m_ErrorString = "", m_FolderName = "", m_FileName = "", m_CurrentMoveFolderName = "";
    bool m_ShowCreateFolderPopup = false, m_ShowMovePopup = false, m_ShowRenamePopup = false;
    QList<QUrl> m_SelectedUrls;
};
