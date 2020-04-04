#pragma once

#include <QObject>
#include <QVariant>

enum class NetworkActionTypes {
    AUTHORIZATION,
    ALBUM_IMAGES
};

struct networkMessage_t {
    int workerIndex;
    QString clientLink;
    QVariant data;
};
Q_DECLARE_METATYPE(networkMessage_t)
