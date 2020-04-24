#include <QtConcurrent>
#include <QFileInfo>

#include "imagemover.h"

ImageMover::ImageMover(QObject *parent) : QObject(parent) {
    m_Watcher = new QFutureWatcher<void>(this);
}

void ImageMover::moveImageAsynch(const QList<QPair<QString, QString>>& changes, const QString& albumPath) {
    auto moveImages = [](const QList<QPair<QString, QString>>& changesList, const QString& path) {
        foreach(QPair changePair, changesList) {
            QDir dir;
            if(!dir.exists(path + "/" + changePair.first)) {
                dir.mkdir(QFileInfo(path + "/" + changePair.first).absolutePath());
            }
            QFile::rename(path + "/" + changePair.second, path + "/" + changePair.first);
        }
    };
    if(m_Watcher->isRunning()) {
        m_ChangesQueue.append(changes);
    } else {
        m_Watcher->setFuture(QtConcurrent::run(moveImages, changes, albumPath));
    }
}
