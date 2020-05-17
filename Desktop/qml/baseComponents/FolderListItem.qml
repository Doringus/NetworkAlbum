import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Item {
    id: root

    property string folderName: "FOLDER"
    property string folderIcon: "\uf07b"
    property bool selected: false

    signal clicked()
    signal doubleClicked()
    signal ctrlClicked()

    width: 200
    height: 50

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: rect
                color: "#18191C"
            }
        }
    ]

    transitions: Transition {
        from: ""
        to: "Hovering"
        reversible: true

        ColorAnimation {
            duration: 100
        }
    }

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "#292B2F"
        border.color: selected ? "#2095D0" : "#202225"
        radius: 8
    }

    Text {
        id: icon
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        font.family: "FontAwesome"
        text: root.folderIcon
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 18
        color: "#B9BBBE"
    }
    Text {
        anchors.top: parent.top
        anchors.left: icon.right
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        elide: Text.ElideRight
        text: root.folderName
        font.weight: Font.DemiBold
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        color: "white"
        font.pointSize: 16
    }
    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered: { root.state='Hovering'}
        onExited: { root.state=''}
        onClicked: {
            if ((mouse.button == Qt.LeftButton) && (mouse.modifiers & Qt.ControlModifier)) {
                root.ctrlClicked()
            } else {
                root.clicked()
            }
        }
        onDoubleClicked: {
            root.doubleClicked()
        }
    }
}
