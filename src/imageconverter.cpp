#include "imageconverter.h"

#include <QImage>
#include <QFuture>
#include <QtConcurrent>
#include <QJsonValue>

ImageConventer::ImageConventer(QObject *parent) : QObject(parent) {

}

QFuture<QList<QImage>> ImageConventer::scaleImages(QStringList paths, QSize size) {
    auto readAndScale = [](QStringList images, QSize size) {
        QList<QImage> result;
        foreach(QString imagePath, images) {
            QImage image(imagePath);
            result.append(image.scaled(size));
        }
        return result;
    };
    return QtConcurrent::run(readAndScale, paths, size);
}

QFuture<QList<QJsonObject>> ImageConventer::scaleAndConvertImages(QFileInfoList imagesInfoList, QSize size) {
    auto readAndConvert = [](QFileInfoList images, QSize size) {
        QList<QJsonObject> result;
        foreach(QFileInfo imageInfo, images) {
            QImage image(imageInfo.absoluteFilePath());
            image = image.scaled(size);
            QBuffer buff;
            buff.open(QIODevice::WriteOnly);
            image.save(&buff, "JPG");
            QByteArray t = buff.data();
            auto encoded = buff.data().toBase64();
            QJsonObject imageObject;
            imageObject.insert("Name", imageInfo.baseName());
            imageObject.insert("OriginPath", imageInfo.fileName());
            imageObject.insert("Data", QLatin1String(encoded));
            result.append(imageObject);
        }
        return result;
    };
    return QtConcurrent::run(readAndConvert, imagesInfoList, size);
}
