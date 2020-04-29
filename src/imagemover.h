#pragma once

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>
#include <QQueue>

class ImageMover : public QObject {
public:
    explicit ImageMover(QObject *parent = nullptr);
    void moveImageAsynch(const QList<QPair<QString, QString>>& changes, const QString& albumPath);
private slots:
    void finished();
signals:
private:
    QFutureWatcher<void> *m_Watcher;  
    QQueue<QPair<QString, QList<QPair<QString, QString>>>> m_ChangesQueue;
};

