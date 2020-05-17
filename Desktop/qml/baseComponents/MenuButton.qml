import QtQuick 2.13
import QtQuick.Controls 2.12

Item {
    id: root

    property string btnColor: "#333337"
    property string btnHoveredColor: "#3f3f44"
    property string btnTitle: "SAMPLE TEXT SAMPLE TEXT"
    property string btnSubText: "SAMPLE TEXT SAMPLE TEXT SAMPLE TEXT"
    property string btnIcon: "\uf0c9"
    property int btnRadius: 6

    signal clicked()

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: rect
                color: btnHoveredColor
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
        id: rect
        anchors.fill: parent
        color: area.hovered ? btnHoveredColor : btnColor
        radius: btnRadius
    }

    Label {
        id: icon
        anchors.left: parent.left
        anchors.top: title.top
        anchors.right: title.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        color: "white"
        font.pointSize: 20
        font.family: "FontAwesome"
        text: btnIcon
    }

    Label {
        id: title
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 65
        anchors.topMargin: 20
        anchors.rightMargin: 20
        clip: true
        wrapMode: Text.WordWrap
        color: "white"
        font.pointSize: 14
        text: btnTitle
    }

    Label {
        id: subText
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.leftMargin: 65
        anchors.topMargin: 10
        anchors.rightMargin: 20
        clip: true
        wrapMode: Text.WordWrap
        color: "#C6C8D2"
        font.pointSize: 10
        text: btnSubText
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
        onEntered: { root.state='Hovering'}
        onExited: { root.state=''}
    }
}
