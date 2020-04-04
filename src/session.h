#pragma once

#include <QObject>
#include <QUrl>
#include <QMap>

class Session {
public:
    explicit Session(QUrl albumPath = QUrl(), bool hasCopy = false, double compress = 50.0f, QString link = QString());
    QUrl getAlbumPath() const;
    bool hasCopy() const;
    double getCompression() const;
    QString getLink() const;

    void setAlbumPath(QUrl url);
    void setLink(QString link);

    friend bool operator==(const Session& left, const Session& right) {
        return left.getLink() == right.getLink() ||
                left.getAlbumPath() == right.getAlbumPath();
    }
private:
    QUrl m_AlbumPath;
    bool m_HasCopy;
    double m_Compress;
    QString m_Link;

};

Q_DECLARE_METATYPE(Session)
