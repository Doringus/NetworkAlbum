import QtQuick 2.14
import QtQuick.Window 2.14
import Qt.labs.folderlistmodel 2.14
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12

import "pages"
import NetworkAlbum 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Network album")

    Connections {
        target: ChangesStore
        onFilesMoved: {
            stack.pop()
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: connectPage
    }
    Component {
        id: connectPage
        ConnectAlbumPage {
            onConnected: stack.push(openAlbum)
        }
    }


    Component {
        id: openAlbum
        OpenAlbumPage {
            albumName: AlbumInfoStore.albumName
            albumSize: AlbumInfoStore.albumSize
            errorString: AlbumInfoStore.errorString
            onCanceled: stack.pop()
            onOpened: {
                stack.push(albumPage)
            }
        }
    }

    Component {
        id: albumPage
        AlbumPage {
            onOpenMove: stack.push(movePage)
            onOpenChat: stack.push(chatPage)
            onOpenAbout: stack.push(aboutPage)
            onOpenImage: stack.push(imagePage)
        }
    }
    Component {
        id: movePage
        MovePage {
            onBack: {
                stack.pop()
            }
        }
    }
    Component {
        id: chatPage
        ChatPage {
            onBack: stack.pop()
        }
    }
    Component {
        id: aboutPage
        AboutPage {
            onBack: stack.pop()
        }
    }
    Component {
        id: imagePage
        ImagePage {
            onBack: stack.pop()
        }
    }
}
