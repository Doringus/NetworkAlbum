#pragma once

#include <QObject>
#include <QUrl>

#include "../base/store.h"
#include "../albumslistmodel.h"
#include "../session.h"
#include "../changeshistorymodel.h"

/*!
 *      \brief The AlbumsStore class is generic store for common elements in client and server album pages
 */
class AlbumStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QUrl albumUrl READ getAlbumUrl NOTIFY albumUrlChanged)
    Q_PROPERTY(QUrl currentFolderUrl READ getCurrentFolderUrl NOTIFY currentFolderUrlChanged)
    Q_PROPERTY(QString albumPageTitle READ getAlbumPageTitle NOTIFY albumPageTitleChanged)
    Q_PROPERTY(bool showImagePopup READ getShowImagePopup NOTIFY showImagePopupChanged)
    Q_PROPERTY(QUrl imageUrl READ getImageUrl NOTIFY imageUrlChanged)
    Q_PROPERTY(QAbstractListModel* conversationModel READ getConversationModel NOTIFY conversationModelChanged)
    Q_PROPERTY(bool showChat READ getShowChat NOTIFY showChatChanged)
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
    bool getShowChat();
signals:
    void albumUrlChanged();
    void currentFolderUrlChanged();
    void albumPageTitleChanged();
    void showImagePopupChanged();
    void imageUrlChanged();
    void conversationModelChanged();
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
    void processOpenInExplorer();

    void setImagePopupVisibility(bool visible);
    void setChatVisibility(bool visible);
protected:
    ConversationModel *m_Conversation;
private:
    QUrl m_CurrentAlbumUrl, m_CurrentFolderUrl, m_ImageUrl;
    QString m_AlbumPageTitle;
    bool m_ShowImagePopup, m_ShowChat = true;
};

