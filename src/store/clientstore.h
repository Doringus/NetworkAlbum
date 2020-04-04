#pragma once

#include <QObject>
#include <QUrl>

#include "../base/store.h"

class ClientStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QUrl albumUrl READ getAlbumUrl NOTIFY albumUrlChanged)
    Q_PROPERTY(QUrl currentFolderUrl READ getCurrentFolderUrl NOTIFY currentFolderUrlChanged)
    Q_PROPERTY(QUrl imageUrl READ getImageUrl NOTIFY imageUrlChanged)
public:

    ClientStore(const ClientStore&) = delete;
    ClientStore& operator=(const ClientStore&) = delete;

    static ClientStore& get() {
        static ClientStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

    QUrl getAlbumUrl();
    QUrl getCurrentFolderUrl();
    QUrl getImageUrl();
signals:
    void albumUrlChanged();
    void currentFolderUrlChanged();
    void imageUrlChanged();
private:
    ClientStore() = default;
private:
    QUrl m_CurrentAlbumUrl, m_CurrentFolderUrl, m_ImageUrl;
};
