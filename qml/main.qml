import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import Qt.labs.folderlistmodel 2.13

import "pages"
import "baseComponents"
import "popups"

import NetworkAlbum 1.0

Window {
    visible: true
    width: 1400
    height: 800
    title: qsTr("Album")

    Connections {
        target: MainStore
        onSessionCreated: {
            ActionProvider.hideCreateSessionPopup();
            stackView.push(albumsPage)
        }
    }

    CreateAlbumPopup {
        id: createAlbumPopup

        errorString: MainStore.errorString

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
            popStackView()
        }
        visible: MainStore.showCreatePopup
    }

    OpenAlbumPopup {
        id: openAlbumPopup
        visible: MainStore.showOpenPopup
        errorString: MainStore.errorString
        onClicked: {
            ActionProvider.connectToAlbum(link)
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
            albumsModel: MainStore.albumsModel
            onOpenAlbum: {
                stackView.push(albumPage)
            }
        }
    }

    Component {
        id: albumPage
        AlbumPage {
            imagesModel: MainStore.albumImagesModel
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
