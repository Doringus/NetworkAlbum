#pragma once

#include <QObject>
#include <QUrl>
#include <QVariant>

/*!
 *      \brief The ActionProvider class provides qml interface for creating actions
 *      \warning ActionProvider is singleton
 */
class ActionProvider : public QObject {
    Q_OBJECT
public:
    ActionProvider(const ActionProvider&) = delete;
    ActionProvider& operator=(const ActionProvider&) = delete;
    static ActionProvider& get() {
        static ActionProvider instance;
        return instance;
    }

    Q_INVOKABLE void openFolder(QUrl folderUrl);
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
    Q_INVOKABLE void reconnectToAlbum();
    Q_INVOKABLE void hideEasterEgg();
    Q_INVOKABLE void getImages();
private:
    ActionProvider() = default;
    ~ActionProvider() = default;
};

