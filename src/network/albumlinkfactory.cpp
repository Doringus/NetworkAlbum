#include "albumlinkfactory.h"

#include <QDebug>

AlbumLinkFactory::AlbumLinkFactory(QObject *parent, QString linkPrefix) : QObject(parent),
                                    m_LinkPrefix(linkPrefix) {
    m_Links.insert("TEST");
}

AlbumLinkFactory::~AlbumLinkFactory() {

}

QString AlbumLinkFactory::getLink() {
    QMutexLocker locker(&m_Mutex);
    return "TEST";
}

bool AlbumLinkFactory::availableLink(QString link) {
    QMutexLocker locker(&m_Mutex);
    return m_Links.contains(link) && !m_ActiveLinks.contains(link);
}

void AlbumLinkFactory::removeActiveLink(QString link) {
    QMutexLocker locker(&m_Mutex);
    m_ActiveLinks.remove(link);
}

void AlbumLinkFactory::removeAlbumLink(QString link) {
    QMutexLocker locker(&m_Mutex);
    m_Links.remove(link);
}
