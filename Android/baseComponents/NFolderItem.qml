import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Item {
    id: root

    property bool selected: false
    property string folderName: "folder"
    property var folderPath

    signal clicked()
    signal chdir()

    height: 40

    states: [
        State {
            name: "Hovered"
            PropertyChanges {
                target: rect
                color: "#F1F1F1"
            }
        },
        State {
            name: "Selected"
            PropertyChanges {
                target: iconLabel
                color: "white"
            }
            PropertyChanges {
                target: folderNameLabel
                color: "white"
            }
            PropertyChanges {
                target: rect
                color: "#4D90FE"
            }
        }

    ]

    onSelectedChanged: {
        if(selected) {
            root.state = "Selected"
        } else {
            root.state = ""
        }
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered: {
            if(root.state != "Selected") {
                root.state="Hovered"
            }
        }
        onExited: {
            if(root.state != "Selected") {
                root.state=''
            }
        }
        onClicked: root.chdir()
    }

    Rectangle {
        id: rect
        anchors.fill: parent

        RowLayout {
            id: row
            anchors.fill: parent
            spacing: 30
            Label {
                id: iconLabel
                Layout.leftMargin: 30
                font.family: "FontAwesome"
                text: "\uf07b"
                color: "#8F8F8F"
                font.pointSize: 14
            }
            Label {
                id: folderNameLabel
                text: root.folderName
                Layout.preferredWidth: 400
                elide: Text.ElideRight
                font.pointSize: 16
            }
        }

    }
}
