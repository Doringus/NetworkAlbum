import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../baseComponents"

Item {
    id: root
    Rectangle {
        id: componentTitle
        anchors.left: parent.left
        anchors.top: parent.top
        width: 240
        height: 50
        color: "#36393F"
        z:2
        Label {
            anchors.fill: parent
            color: "white"
            text: "Мои альбомы"
            font.weight: Font.DemiBold
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
        }
    }

    Rectangle {
        id: toolBar
        anchors.left: componentTitle.right
        anchors.top: parent.top
        anchors.right: parent.right
        height: 50
        color: "#36393F"
        z:2
        RowLayout {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            NToolButton {
                icon: "\uf013"
                pointSize: 16
                toolTip: "Настройки"
            }
            ToolSeparator { }
            NToolButton {
                icon: "\uf128"
                pointSize: 16
                toolTip: "Помощь"
            }
        }
    }

    Rectangle {
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: toolBar.bottom
        height: 2
        z:2
        color: "#2B2E33"
    }


    Loader {
        id: loader
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
        sourceComponent: album
    }

    Component {
        id: albums
        AlbumsPage {

        }
    }

    Component {
        id: album
        AlbumPage {

        }
    }
}
