import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property string imagePath: "none"
    property string albumName: "Новый альбом"

    signal clicked()

    width: 330
    height: 210

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: rect
                radius: 10
            }
        }
    ]

    transitions: Transition {
        from: ""
        to: "Hovering"
        reversible: true

        PropertyAnimation {
            duration: 150
            properties: "radius"
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        Rectangle {
            id: rect
            anchors.fill: parent
            color: "#5a000000"
            radius: 28
        }

        Image {
            anchors.fill: parent
            source: imagePath
            sourceSize.width: root.width
            sourceSize.height: root.height
        }
        Label {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 20
            anchors.bottomMargin: 20
            width: 200
            font.pointSize: 14
            color: "white"
            text: root.albumName
            clip: false
            elide: Text.ElideRight
            font.weight: Font.DemiBold
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onEntered: { root.state='Hovering'}
            onExited: { root.state=''}
            onClicked: {
                root.clicked()
            }

            NToolButton {
                id: moreActionBtn
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.rightMargin: 20
                icon: "\uf142"
                toolTip: "Ещё"
                onClicked: menu.open()
            }
            Menu {
                id: menu
                y: moreActionBtn.y + moreActionBtn.height
                x: moreActionBtn.x - width / 2
                width: 210
                topPadding: 10

                Action { text: qsTr("Открыть"); icon.name: "\uf07c"; }
                Action { text: qsTr("Копировать ссылку"); icon.name: "\uf064"; }
                Action { text: qsTr("Закрыть альбом"); icon.name: "\uf00d";}

                delegate: NMenuItem{}
                background: Rectangle {
                    implicitWidth: 210
                    implicitHeight: 40 * menu.count + 20
                    color: "#18191C"
                    radius: 4
                }

            }
        }

    }
}
