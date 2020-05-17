import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property string albumName: "\uf067\nНовый альбом"

    signal clicked()

    width: 300
    height: 180

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: label
                color: "#39A5DB"
            }
        }
    ]

    transitions: Transition {
        from: ""
        to: "Hovering"
        reversible: true

        ColorAnimation {
            duration: 200
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
        Label {
            id: label
            anchors.fill: parent
            font.pointSize: 14
            color: "white"
            text: root.albumName
            font.family: "FontAwesome"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
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

        }

    }
}
