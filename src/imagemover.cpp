#include <QtConcurrent>
#include <QFileInfo>

#include "imagemover.h"

ImageMover::ImageMover(QObject *parent) : QObject(parent) {
    m_Watcher = new QFutureWatcher<void>(this);
    connect(m_Watcher, &QFutureWatcher<void>::finished, this, &ImageMover::finished);
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
        m_ChangesQueue.append({albumPath, changes});
    } else {
        m_Watcher->setFuture(QtConcurrent::run(moveImages, changes, albumPath));
    }
}

void ImageMover::finished() {
    if(m_ChangesQueue.size() != 0) {
        moveImageAsynch(m_ChangesQueue.dequeue().second, m_ChangesQueue.dequeue().first);
    }
}

