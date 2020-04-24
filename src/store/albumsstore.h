#pragma once

#include <QObject>

#include "../base/store.h"
#include "../albumslistmodel.h"
#include "../session.h"

class AlbumsStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(bool showLinkPopup READ getShowLinkPopup NOTIFY showLinkPopupChanged)
    Q_PROPERTY(QString albumGlobalLink READ getAlbumGlobalLink NOTIFY albumGlobalLinkChanged)
    Q_PROPERTY(QString albumLocalLink READ getAlbumLocalLink NOTIFY albumLocalLinkChanged)
    Q_PROPERTY(QAbstractListModel* albumsModel READ getAlbumsModel NOTIFY albumsModelChanged)
public:
    AlbumsStore(const AlbumsStore&) = delete;
    AlbumsStore& operator=(const AlbumsStore&) = delete;

    static AlbumsStore& get() {
        static AlbumsStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);
    bool getShowLinkPopup();
    QString getAlbumGlobalLink();
    QString getAlbumLocalLink();
    QAbstractListModel* getAlbumsModel();
signals:
    void showLinkPopupChanged();
    void albumGlobalLinkChanged();
    void albumLocalLinkChanged();
    void albumsModelChanged();
private:
    AlbumsStore() = default;
    void processAddAlbum(const Session& session);
    void setShowLinkPopupVisibility(bool visible);
    void processShowAlbumLinks(int index);
private:
    AlbumsListModel m_Albums;
    int m_CurrentAlbumIndex;
    bool m_ShowLinkPopup;
    QString m_GlobalLink, m_LocalLink;
};

