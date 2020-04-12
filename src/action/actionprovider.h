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
    Q_INVOKABLE void openAlbum(int index);
    Q_INVOKABLE void openFolder(QUrl folderUrl);
    Q_INVOKABLE void hideCreateSessionPopup();
    Q_INVOKABLE void openCreateSessionPopup();
    Q_INVOKABLE void showOpenPopup();
    Q_INVOKABLE void hideOpenPopup();
    Q_INVOKABLE void openImagePopup(QUrl imageUrl);
    Q_INVOKABLE void hideImagePopup();
    Q_INVOKABLE void connectToAlbum(QString link);
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
private:
    ActionProvider() = default;
    ~ActionProvider() = default;
};

