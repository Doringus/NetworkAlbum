#pragma once

#include <QObject>

#include "../base/store.h"
#include "../albumslistmodel.h"
#include "../session.h"

class AlbumsStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(bool showLinkPopup READ getShowLinkPopup NOTIFY showLinkPopupChanged)
    Q_PROPERTY(bool showSettingsPopup READ getShowSettingsPopup NOTIFY showSettingsPopupChanged)
    Q_PROPERTY(bool showAlbumSettings READ getShowAlbumSettings NOTIFY showAlbumSettingsChanged)
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
    bool getShowSettingsPopup();
    bool getShowAlbumSettings();
signals:
    void showLinkPopupChanged();
    void albumGlobalLinkChanged();
    void albumLocalLinkChanged();
    void albumsModelChanged();
    void showSettingsPopupChanged();
    void showAlbumSettingsChanged();
private:
    AlbumsStore() = default;
    void processAddAlbum(const Session& session);
    void setShowLinkPopupVisibility(bool visible);
    void processShowAlbumLinks(int index);
    void processReceiveMessage(const QString& link);
    void setSettingPopupVisibility(bool visible);
    void setShowAlbumSettings(bool visible);
    void processImageSync(const QString& link);
private:
    AlbumsListModel m_Albums;
    int m_CurrentAlbumIndex = -1;
    bool m_ShowLinkPopup, m_ShowSettingsPopup, m_ShowAlbumSettings;
    QString m_GlobalLink, m_LocalLink;
};

