import QtQuick 2.13
import QtQuick.Window 2.13
import Qt.labs.folderlistmodel 2.13

Window {
    visible: true
    width: 1200
    height: 800
    title: qsTr("Album")
    Loader {
        sourceComponent: startupMenu
        anchors.fill: parent
        asynchronous: true
    }

    Component {
        id: startupMenu
        StartupMenu {

        }
    }
}
