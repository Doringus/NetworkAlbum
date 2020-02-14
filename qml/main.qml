import QtQuick 2.13
import QtQuick.Window 2.13
import Qt.labs.folderlistmodel 2.13

import "pages"

Window {
    visible: true
    width: 1200
    height: 800
    title: qsTr("Album")
    Loader {
        id: loader
        sourceComponent: mainServerPage
        anchors.fill: parent
        asynchronous: true
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
