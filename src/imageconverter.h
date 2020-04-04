#pragma once

#include <QObject>
#include <QFuture>
#include <QJsonObject>
#include <QFileInfoList>

class ImageConventer : public QObject {
    Q_OBJECT
public:
    explicit ImageConventer(QObject *parent = nullptr);
    QFuture<QList<QImage>> scaleImages(QStringList paths, QSize size);
    QFuture<QList<QJsonObject> > scaleAndConvertImages(QFileInfoList imagesInfoList, QSize size);
signals:

};

