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

QFuture<QList<QJsonObject>> ImageConventer::scaleAndConvertImages(QFileInfoList imagesInfoList, double scale) {
    auto readAndConvert = [](QFileInfoList images, double scale) {
        QList<QJsonObject> result;
        foreach(QFileInfo imageInfo, images) {
            QImage image(imageInfo.absoluteFilePath());
            image = image.scaled(image.size() * scale / 100.0f);
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
    return QtConcurrent::run(readAndConvert, imagesInfoList, scale);
}

QFuture<QList<QJsonObject>> ImageConventer::convertImages(QFileInfoList imagesInfoList) {
    auto readAndConvert = [](QFileInfoList images) {
        QList<QJsonObject> result;
        foreach(QFileInfo imageInfo, images) {
            QImage image(imageInfo.absoluteFilePath());
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
    return QtConcurrent::run(readAndConvert, imagesInfoList);
}
