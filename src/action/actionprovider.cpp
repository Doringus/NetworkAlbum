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

void ActionProvider::connectToAlbum(QString link, bool scaledImages) {
    QVariant data = QVariant::fromValue<QPair<QString, bool>>(QPair<QString, bool>(link, scaledImages));
    Dispatcher::get().dispatch(new Action(ActionType::CONNECT_TO_ALBUM, data));
}

void ActionProvider::createFolder(QString folderName) {
    Dispatcher::get().dispatch(new Action(ActionType::CREATE_FOLDER, folderName));
}

void ActionProvider::showCreateFolderPopup() {
    Dispatcher::get().dispatch(new Action(ActionType::SHOW_CREATE_FOLDER_POPUP));
}

void ActionProvider::hideCreateFolderPopup() {
    Dispatcher::get().dispatch(new Action(ActionType::HIDE_CREATE_FOLDER_POPUP));
}

void ActionProvider::selectFile(QUrl url) {
    Dispatcher::get().dispatch(new Action(ActionType::SELECT_FILE, url));
}

void ActionProvider::deselectFiles() {
    Dispatcher::get().dispatch(new Action(ActionType::DESELECT_FILES));
}

void ActionProvider::clearAllAndSelectFile(QUrl url) {
    Dispatcher::get().dispatch(new Action(ActionType::CLEAR_AND_SELECT_FILES, url));
}

void ActionProvider::deselectFile(QUrl url) {
    Dispatcher::get().dispatch(new Action(ActionType::DESELECT_FILE, url));
}

void ActionProvider::changeMoveDir(QUrl url) {
    Dispatcher::get().dispatch(new Action(ActionType::CHANGE_MOVE_DIR, url));
}

void ActionProvider::moveFiles(QUrl dest) {
    Dispatcher::get().dispatch(new Action(ActionType::MOVE_FILES, dest));
}

void ActionProvider::showMovePopup() {
    Dispatcher::get().dispatch(new Action(ActionType::SHOW_MOVE_POPUP));
}

void ActionProvider::hideMovePopup() {
    Dispatcher::get().dispatch(new Action(ActionType::HIDE_MOVE_POPUP));
}

void ActionProvider::renameFile(QString name) {
    Dispatcher::get().dispatch(new Action(ActionType::RENAME_FILE, name));
}

void ActionProvider::showRenamePopup() {
    Dispatcher::get().dispatch(new Action(ActionType::SHOW_RENAME_POPUP));
}

void ActionProvider::hideRenamePopup() {
    Dispatcher::get().dispatch(new Action(ActionType::HIDE_RENAME_POPUP));
}

void ActionProvider::deleteFiles() {
    Dispatcher::get().dispatch(new Action(ActionType::DELETE_FILES));
}

void ActionProvider::syncImages() {
    Dispatcher::get().dispatch(new Action(ActionType::SYNC_IMAGES));
}

void ActionProvider::sendMessage(QString message) {
    Dispatcher::get().dispatch(new Action(ActionType::BEGIN_SEND_MESSAGE, message));
}

void ActionProvider::showLinkPopup(int index) {
    Dispatcher::get().dispatch(new Action(ActionType::SHOW_LINK_POPUP, index));
}

void ActionProvider::hideLinkPopup() {
    Dispatcher::get().dispatch(new Action(ActionType::HIDE_LINK_POPUP));
}
