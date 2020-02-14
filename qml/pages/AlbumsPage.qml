import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../baseComponents"

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "#2F3136"
    }
    GridView {
        id: grid
        anchors.fill: parent
        anchors.leftMargin: 50
        anchors.topMargin: 50
        boundsBehavior: Flickable.StopAtBounds
        flow: GridView.LeftToRight
        snapMode: GridView.SnapToRow
        cacheBuffer: 0
        model: 20
        cellHeight: 240
        cellWidth: 360
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            contentItem: Rectangle {
                implicitWidth: 6
                implicitHeight: 100
                radius: width / 2
                color: "#9A9A9C"
            }
        }

        delegate: AlbumListItem {

        }
    }
}
