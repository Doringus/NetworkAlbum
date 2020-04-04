#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QAbstractItemModel>
#include <QFileSystemModel>

#include "../base/store.h"
#include "../session.h"
#include "../albumslistmodel.h"
#include "../network/networkactiontypes.h"

class MainStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(bool showCreatePopup READ getShowCreatePopup NOTIFY showCreatePopupChanged)
    Q_PROPERTY(bool showOpenPopup READ getShowOpenPopup NOTIFY showOpenPopupChanged)
    Q_PROPERTY(QAbstractListModel* albumsModel READ getAlbumsModel NOTIFY albumsModelChanged)
    Q_PROPERTY(QUrl albumUrl READ getAlbumUrl NOTIFY albumUrlChanged)
    Q_PROPERTY(QUrl currentFolderUrl READ getCurrentFolderUrl NOTIFY currentFolderUrlChanged)
    Q_PROPERTY(QString albumPageTitle READ getAlbumPageTitle NOTIFY albumPageTitleChanged)
    Q_PROPERTY(bool showImagePopup READ getShowImagePopup NOTIFY showImagePopupChanged)
    Q_PROPERTY(QUrl imageUrl READ getImageUrl NOTIFY imageUrlChanged)
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorStringChanged)
public:

    MainStore(const MainStore&) = delete;
    MainStore& operator=(const MainStore&) = delete;

    static MainStore& get() {
        static MainStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

    bool getShowCreatePopup();
    bool getShowOpenPopup();
    QString getErrorText();
    QAbstractListModel* getAlbumsModel();
    QUrl getAlbumUrl();
    QUrl getCurrentFolderUrl();
    QString getAlbumPageTitle();
    bool getShowImagePopup();
    QUrl getImageUrl();
    QString getErrorString();
signals:
    void showCreatePopupChanged();
    void showOpenPopupChanged();
    void albumsModelChanged();
    void albumUrlChanged();
    void currentFolderUrlChanged();
    void albumPageTitleChanged();
    void showImagePopupChanged();
    void imageUrlChanged();
    void errorStringChanged();

    void sessionCreated();
private:
    MainStore();
    ~MainStore() = default;

    void processShowCreatePopup();
    void processHideCreatePopup();
    void processShowOpenPopup();
    void processHideOpenPopup();
    void processCreateAlbum(Session session);
    void processOpenAlbum(int index);
    void processOpenFolder(QUrl folder);
    void processOpenImagePopup(QUrl imageUrl);
    void processHideImagePopup();
    void processShowError(QString errorString);
    void processSendImages(networkMessage_t message);
private:
    AlbumsListModel m_Albums;
    QList<Session> m_Sessions;
    QUrl m_CurrentAlbumUrl, m_CurrentFolderUrl, m_ImageUrl;
    QString m_AlbumPageTitle, m_ErrorString;
    bool m_ShowCreatePopup, m_ShowOpenPopup, m_ShowImagePopup;
};

