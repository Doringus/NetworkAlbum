#pragma once

#include <QObject>
#include <QUrl>

class Session {
public:
    explicit Session(QUrl albumPath = QUrl(), bool hasCopy = false, double compress = 50.0f);
    QUrl getAlbumPath() const;
    bool hasCopy() const;
    double getCompression() const;

    void setAlbumPath(QUrl url);

private:
    QUrl m_AlbumPath;
    bool m_HasCopy;
    double m_Compress;

};
Q_DECLARE_METATYPE(Session)
