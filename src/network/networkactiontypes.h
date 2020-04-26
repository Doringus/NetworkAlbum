#pragma once

#include <QObject>
#include <QVariant>

enum class NetworkActionTypes {
    AUTHORIZATION,
    ALBUM_IMAGES,
    SYNC,
    CONVERSATION,
    DISCONNECT
};

struct networkMessage_t {
    QString clientLink;
    QVariant data;

    networkMessage_t()
    { }
    networkMessage_t(const networkMessage_t& e) :
                                        clientLink(e.clientLink),
                                        data(e.data)
    { }
    networkMessage_t(networkMessage_t&& e) noexcept:
                                        clientLink(std::move(e.clientLink)),
                                        data(std::move(e.data))
    { }
};
Q_DECLARE_METATYPE(networkMessage_t)
