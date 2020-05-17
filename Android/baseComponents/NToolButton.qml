import QtQuick 2.13
import QtQuick.Controls 2.12


Item {
    id: root
    property color iconColor: "#B9BBBE"
    property color iconHoveredColor: "#DCDDDE"
    property string icon: "\uf002"
    property string toolTip: "tip"
    property int pointSize: 12

    signal clicked()

    height: 25
    width: 25

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        Label {
            id: icon
            anchors.fill: parent
            color: root.iconColor
            font.family: "FontAwesome"
            font.pointSize: root.pointSize
            text: root.icon
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        NToolTip {
            id: toolTip
            text: root.toolTip
            visible: false
        }
    }

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: icon
                color: root.iconHoveredColor
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

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            toolTip.close()
            root.clicked()
        }
        onEntered: { root.state='Hovering'}
        onExited: { root.state=''}
    }
}
