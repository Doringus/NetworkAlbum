#pragma once

#include <QObject>
#include <QUrl>

#include "../base/store.h"
#include "../albumslistmodel.h"
#include "../session.h"

class AlbumStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QUrl albumUrl READ getAlbumUrl NOTIFY albumUrlChanged)
    Q_PROPERTY(QUrl currentFolderUrl READ getCurrentFolderUrl NOTIFY currentFolderUrlChanged)
    Q_PROPERTY(QString albumPageTitle READ getAlbumPageTitle NOTIFY albumPageTitleChanged)
    Q_PROPERTY(bool showImagePopup READ getShowImagePopup NOTIFY showImagePopupChanged)
    Q_PROPERTY(QUrl imageUrl READ getImageUrl NOTIFY imageUrlChanged)
    Q_PROPERTY(QAbstractListModel* conversationModel READ getConversationModel NOTIFY conversationModelChanged)
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
    QAbstractListModel* getConversationModel();
signals:
    void albumUrlChanged();
    void currentFolderUrlChanged();
    void albumPageTitleChanged();
    void showImagePopupChanged();
    void imageUrlChanged();
    void conversationModelChanged();
private:
    AlbumStore() = default;
    void processOpenAlbum();
    void processOpenFolder(const QUrl& folder);
    void processOpenImagePopup(const QUrl& imageUrl);

    void setImagePopupVisibility(bool visible);
private:
    QUrl m_CurrentAlbumUrl, m_CurrentFolderUrl, m_ImageUrl;
    QString m_AlbumPageTitle;
    ConversationModel *m_Conversation;
    bool m_ShowImagePopup;
};

