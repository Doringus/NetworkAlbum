#pragma once

#include <QObject>
#include <QUrl>
#include <QDir>

#include "../base/store.h"


class AlbumStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QUrl albumUrl READ getAlbumUrl NOTIFY albumUrlChanged)
    Q_PROPERTY(QUrl currentFolderUrl READ getCurrentFolderUrl NOTIFY currentFolderUrlChanged)
    Q_PROPERTY(QString albumPageTitle READ getAlbumPageTitle NOTIFY albumPageTitleChanged)
    Q_PROPERTY(bool showImagePopup READ getShowImagePopup NOTIFY showImagePopupChanged)
    Q_PROPERTY(QUrl imageUrl READ getImageUrl NOTIFY imageUrlChanged)
public:
    AlbumStore(const AlbumStore&) = delete;
    AlbumStore& operator=(const AlbumStore&) = delete;

    static AlbumStore& get() {
        static AlbumStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

    QUrl getAlbumUrl();
    QUrl getCurrentFolderUrl();
    QUrl getImageUrl();
    QString getAlbumPageTitle();
    bool getShowImagePopup();
signals:
    void albumUrlChanged();
    void currentFolderUrlChanged();
    void albumPageTitleChanged();
    void showImagePopupChanged();
    void imageUrlChanged();
    void showChatChanged();
protected:
    AlbumStore() = default;
    void setAlbumUrl(const QUrl& url);
    void setCurrentFolderUrl(const QUrl& url);
    void setImageUrl(const QUrl& url);
    void setAlbumPageTitle(const QString& title);
    void setShowImagePopupVisibility(bool visible);
private: 
    void processOpenFolder(const QUrl& folder);
    void processOpenImagePopup(const QUrl& imageUrl);
    void processReceiveImages(const QJsonObject& images);
    void processSetAlbumName(const QString& albumName);

    void setImagePopupVisibility(bool visible);
private:
    QUrl m_CurrentAlbumUrl, m_CurrentFolderUrl, m_ImageUrl;
    QString m_AlbumPageTitle;
    bool m_ShowImagePopup, m_ShowChat = true;
    QString m_AlbumName;
};

