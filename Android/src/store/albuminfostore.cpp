#include "albuminfostore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"

void AlbumInfoStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::RECEIVE_ALBUM_INFO: {
            processReceiveAlbumInfo(action->getData<QPair<QString, double>>().first, action->getData<QPair<QString, double>>().second);
            break;
        }
        case ActionType::CLIENT_CONNECTED: {
            processShowError(action->getErrorString());
            break;
        }
    }
}

QString AlbumInfoStore::getAlbumName() {
    return m_AlbumName;
}

double AlbumInfoStore::getAlbumSize() {
    return m_AlbumSize;
}

QString AlbumInfoStore::getErrorString() {
    return m_ErrorString;
}

void AlbumInfoStore::processReceiveAlbumInfo(const QString &albumName, double albumSize) {
    m_AlbumName = albumName;
    m_AlbumSize = albumSize;
    emit albumNameChanged();
    emit albumSizeChanged();
}

void AlbumInfoStore::processShowError(const QString &errorString) {
    m_ErrorString = errorString;
    emit errorStringChanged();
}
