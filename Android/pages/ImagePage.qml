import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import "../popups"
import NetworkAlbum 1.0

Page {
    signal back()
    header: Rectangle {
        height: 50
        color: "#36393F"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            NToolButton {
                Layout.alignment: Qt.AlignLeft
                icon: "\uf060"
                iconColor: "#87909C"
                toolTip: "Назад"
                height: 50
                onClicked: {
                    back()
                }
            }
            Label {
                font.pointSize: 18
                color: "white"
                text: ""
            }
        }
    }
    Image {
        anchors.fill: parent
        source: AlbumStore.imageUrl
    }
}
