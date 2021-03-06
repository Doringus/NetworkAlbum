#pragma once

enum class ActionType {
    OPEN_CREATION_POPUP,
    HIDE_CREATION_POPUP,
    OPEN_CONNECT_POPUP,
    HIDE_CONNECT_POPUP,
    CREATE_SESSION,
    SESSION_CREATED,
    OPEN_ALBUM,
    OPEN_RESERVE_ALBUM,
    OPEN_IN_EXPLORER,
    RETURN_TO_ALBUMS_PAGE,
    OPEN_FOLDER,
    CLOSE_SESSION,
    OPEN_IMAGE_POPUP,
    HIDE_IMAGE_POPUP,
    CONNECT_TO_ALBUM,
    BEGIN_SEND_IMAGES,
    SEND_ALBUM_INFO,
    BEGIN_SEND_ALBUM_INFO,
    HIDE_GET_IMAGES_POPUP,
    GET_IMAGES,
    RECEIVE_ALBUM_INFO,
    SEND_IMAGES,
    SEND_MESSAGE,
    BEGIN_SEND_MESSAGE,
    RECEIVE_MESSAGE,
    START_SERVER,
    CLIENT_CONNECTED,
    IMAGES_RECEIVED,
    CREATE_FOLDER,
    HIDE_CREATE_FOLDER_POPUP,
    SHOW_CREATE_FOLDER_POPUP,
    SELECT_FILE,
    DESELECT_FILES,
    DESELECT_FILE,
    CLEAR_AND_SELECT_FILES,
    CHANGE_MOVE_DIR,
    MOVE_FILES,
    SHOW_MOVE_POPUP,
    HIDE_MOVE_POPUP,
    SHOW_RENAME_POPUP,
    HIDE_RENAME_POPUP,
    RENAME_FILE,
    DELETE_FILES,
    SYNC_IMAGES,
    SEND_SYNC_DATA,
    RECEIVE_SYNC_DATA,
    SHOW_LINK_POPUP,
    HIDE_LINK_POPUP,
    SHOW_SETTINGS_POPUP,
    HIDE_SETTINGS_POPUP,
    SHOW_CHAT,
    HIDE_CHAT,
    SAVE_SETTINGS,
    CLOSE_WINDOW,
    CLIENT_DISCONNECTED,
    HIDE_RECONNECT_POPUP,
    RECONNECT_TO_ALBUM,
    HIDE_EASTER_EGG_POPUP,
    SHOW_HELP_POPUP,
    HIDE_HELP_POPUP
};
