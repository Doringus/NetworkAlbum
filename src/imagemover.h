#pragma once

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>
#include <QQueue>

class ImageMover : public QObject {
public:
    explicit ImageMover(QObject *parent = nullptr);
    void moveImageAsynch(const QList<QPair<QString, QString>>& changes, const QString& albumPath);
signals:
private:
    QFutureWatcher<void> *m_Watcher;
    QQueue<QList<QPair<QString, QString>>> m_ChangesQueue;
};

