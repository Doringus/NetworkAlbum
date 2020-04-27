import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import Qt.labs.folderlistmodel 2.13

import "pages"
import "baseComponents"
import "popups"

import NetworkAlbum 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1400
    height: 800
    title: qsTr("Album")

    onClosing: {
        if(NotificationStore.closableWindow) {
            Qt.quit()
        } else {
            close.accepted = false
            hide()
        }
    }

    Connections {
        target: RootStore
        onSessionCreated: {
            ActionProvider.hideCreateSessionPopup();
            stackView.push(albumsPage)
        }
    }

    Connections {
        target: ClientStore
        onConnectedToAlbum: {
            ActionProvider.hideOpenPopup()
            stackView.push(clientAlbumPage)
        }
    }

    Connections {
        target: NotificationStore
        onShowWindow: {
            window.show()
        }
        onCloseWindow: {
            Qt.quit()
        }
    }

    CreateAlbumPopup {
        id: createAlbumPopup

        errorString: RootStore.errorString

        enter: Transition {
            NumberAnimation {
                property: "opacity"
                easing.type: Easing.InOutQuad;
                from: 0.2
                to: 1.0
            }
        }
        onAboutToHide: {      
            ActionProvider.hideCreateSessionPopup()
        }
        onCreated: {
            ActionProvider.createSession(albumUrl, hasReserveFolder, imageScale)
        }
        visible: RootStore.showCreatePopup
    }

    OpenAlbumPopup {
        id: openAlbumPopup
        visible: RootStore.showOpenPopup
        errorString: RootStore.errorString
        onClicked: {
            ActionProvider.connectToAlbum(link, scaled)
        }
        onAboutToHide: {
            ActionProvider.hideOpenPopup()
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: startupMenu
        popEnter: Transition{}
        popExit: Transition{}
        pushEnter: Transition{}
        pushExit: Transition{}
    }

    Component {
        id: albumsPage
        AlbumsPage {
            albumsModel: AlbumsStore.albumsModel
            onOpenAlbum: {
                stackView.push(albumPage)
            }
        }
    }
    Component {
        id: clientAlbumPage
        ClientAlbumPage {

        }
    }

    Component {
        id: albumPage
        AlbumPage {

        }
    }

    Component {
        id: startupMenu
        StartupMenu {
        }
    }

    Component {
        id: mainServerPage
        MainServerPage {

        }
    }
}
