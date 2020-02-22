import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import Qt.labs.folderlistmodel 2.13

import "pages"

Window {
    visible: true
    width: 1400
    height: 800
    title: qsTr("Album")
   /* Loader {
        id: loader
        sourceComponent: mainServerPage
        anchors.fill: parent
        asynchronous: true
    }*/
    StackView {
      // Component.onCompleted: {push(albumsPage); push(albumPage)}
        anchors.fill: parent
        initialItem: startupMenu
    }

    Component {
        id: albumsPage
        AlbumsPage{}
    }

    Component {
        id: albumPage
        AlbumPage{}
    }

    Component {
        id: startupMenu
        StartupMenu {
            onOpenServer: {
                loader.sourceComponent = mainServerPage
            }
        }
    }

    Component {
        id: mainServerPage
        MainServerPage {

        }
    }
}
