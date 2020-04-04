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
private:
    ActionProvider() = default;
    ~ActionProvider() = default;
};

