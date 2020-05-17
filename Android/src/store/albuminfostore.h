#pragma once

#include <QObject>

#include "../base/store.h"

class AlbumInfoStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QString albumName READ getAlbumName NOTIFY albumNameChanged)
    Q_PROPERTY(double albumSize READ getAlbumSize NOTIFY albumSizeChanged)
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorStringChanged)
public:
    AlbumInfoStore(const AlbumInfoStore&) = delete;
    AlbumInfoStore& operator=(const AlbumInfoStore&) = delete;

    static AlbumInfoStore& get() {
        static AlbumInfoStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);

    QString getAlbumName();
    double getAlbumSize();
    QString getErrorString();
private:
    AlbumInfoStore() = default;
    void processReceiveAlbumInfo(const QString& albumName, double albumSize);
    void processShowError(const QString& errorString);
signals:
    void albumNameChanged();
    void albumSizeChanged();
    void errorStringChanged();
private:
    QString m_AlbumName, m_ErrorString;
    double m_AlbumSize;
};

