#pragma once

#include <QObject>
#include <QUrl>
#include <QVariant>

class ActionProvider : public QObject {
    Q_OBJECT
public:
    ActionProvider(const ActionProvider&) = delete;
    ActionProvider& operator=(const ActionProvider&) = delete;
    static ActionProvider& get() {
        static ActionProvider instance;
        return instance;
    }

    Q_INVOKABLE void createSession(QString albumPath, bool hasCopy, double compress);
    Q_INVOKABLE void closeSession(int index);
    Q_INVOKABLE void openAlbum(int index);
    Q_INVOKABLE void openReserveAlbum(int index);
    Q_INVOKABLE void openInExplorer();
    Q_INVOKABLE void returnToAlbumsPage();
    Q_INVOKABLE void openFolder(QUrl folderUrl);
    Q_INVOKABLE void hideCreateSessionPopup();
    Q_INVOKABLE void openCreateSessionPopup();
    Q_INVOKABLE void showOpenPopup();
    Q_INVOKABLE void hideOpenPopup();
    Q_INVOKABLE void openImagePopup(QUrl imageUrl);
    Q_INVOKABLE void hideImagePopup();
    Q_INVOKABLE void connectToAlbum(QString link, bool scaledImages);
    Q_INVOKABLE void createFolder(QString folderName);
    Q_INVOKABLE void showCreateFolderPopup();
    Q_INVOKABLE void hideCreateFolderPopup();
    Q_INVOKABLE void selectFile(QUrl url);
    Q_INVOKABLE void deselectFiles();
    Q_INVOKABLE void clearAllAndSelectFile(QUrl url);
    Q_INVOKABLE void deselectFile(QUrl url);
    Q_INVOKABLE void changeMoveDir(QUrl url);
    Q_INVOKABLE void moveFiles(QUrl dest);
    Q_INVOKABLE void showMovePopup();
    Q_INVOKABLE void hideMovePopup();
    Q_INVOKABLE void renameFile(QString name);
    Q_INVOKABLE void showRenamePopup();
    Q_INVOKABLE void hideRenamePopup();
    Q_INVOKABLE void deleteFiles();
    Q_INVOKABLE void syncImages();
    Q_INVOKABLE void sendMessage(QString message);
    Q_INVOKABLE void showLinkPopup(int index);
    Q_INVOKABLE void hideLinkPopup();
    Q_INVOKABLE void showSettingsPopup();
    Q_INVOKABLE void hideSettingsPopup();
    Q_INVOKABLE void showChat();
    Q_INVOKABLE void hideChat();
    Q_INVOKABLE void saveSettings(bool showNotifications, bool closeWindow);
private:
    ActionProvider() = default;
    ~ActionProvider() = default;
};

