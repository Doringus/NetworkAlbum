#include "actionprovider.h"
#include "../base/dispatcher.h"
#include "actiontypes.h"

void ActionProvider::createSession(QString albumPath, bool hasCopy, double compress) {
    QList<QVariant> args = {QVariant(albumPath), QVariant(hasCopy), QVariant(compress)};
    Dispatcher::get().dispatch(new Action(ActionType::CREATE_SESSION, args));
}

void ActionProvider::openAlbum(int index) {
    Dispatcher::get().dispatch(new Action(ActionType::OPEN_ALBUM, index));
}

void ActionProvider::openFolder(QUrl folderUrl) {
    Dispatcher::get().dispatch(new Action(ActionType::OPEN_FOLDER, folderUrl));
}

void ActionProvider::hideCreateSessionPopup() {
    Dispatcher::get().dispatch(new Action(ActionType::HIDE_CREATION_POPUP));
}

void ActionProvider::openCreateSessionPopup() {
    Dispatcher::get().dispatch(new Action(ActionType::OPEN_CREATION_POPUP));
}

void ActionProvider::showOpenPopup() {
    Dispatcher::get().dispatch(new Action(ActionType::OPEN_CONNECT_POPUP));
}

void ActionProvider::hideOpenPopup() {
    Dispatcher::get().dispatch(new Action(ActionType::HIDE_CONNECT_POPUP));
}

void ActionProvider::openImagePopup(QUrl imageUrl) {
    Dispatcher::get().dispatch(new Action(ActionType::OPEN_IMAGE_POPUP, imageUrl));
}

void ActionProvider::hideImagePopup() {
    Dispatcher::get().dispatch(new Action(ActionType::HIDE_IMAGE_POPUP));
}

void ActionProvider::connectToAlbum(QString link) {
    Dispatcher::get().dispatch(new Action(ActionType::CONNECT_TO_ALBUM, link));
}
