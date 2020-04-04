#pragma once

#include <QObject>
#include <QMutex>
#include <QSet>

class AlbumLinkFactory : public QObject {
    Q_OBJECT
public:
    explicit AlbumLinkFactory(QObject *parent = nullptr, QString linkPrefix = "");
    ~AlbumLinkFactory();
    QString getLink();
    Q_INVOKABLE bool availableLink(QString link);
    void removeActiveLink(QString link);
    void removeAlbumLink(QString link);
private:
    QSet<QString> m_Links;
    QSet<QString> m_ActiveLinks;
    QMutex m_Mutex;
    QString m_LinkPrefix;
};

