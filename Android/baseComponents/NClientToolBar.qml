import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    width: 600
    height: 50

    property alias pageTitle: pageTitleLabel.text
    property alias backButtonVisible: backButton.visible

    signal backButtonClicked()
    signal sendImagesButtonClicked()
    signal openChat()
    signal openHelp()
    signal createFolder()

    Rectangle {
        id: componentTitle
        anchors.left: parent.left
        anchors.top: parent.top
        width: 240
        height: 50
        color: "#36393F"
        NToolButton {
            id: backButton
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            icon: "\uf060"
            onClicked: backButtonClicked()
            toolTip: "Назад"
        }

        Label {
            id: pageTitleLabel
            anchors.fill: parent
            anchors.leftMargin: 20
            color: "white"
            text: "Альбом"
            elide: "ElideRight"
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
        RowLayout {
            id: sideButtons
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            NToolButton {
                icon: "\uf093"
                pointSize: 16
                onClicked: sendImagesButtonClicked()
            }
            NToolButton {
                icon: "\uf067"
                pointSize: 16
                onClicked: createFolder()
            }
            NToolButton {
                icon: "\uf059"
                pointSize: 16
                onClicked: openHelp()
            }
            NToolButton {
                icon: "\uf0e6"
                pointSize: 16
                onClicked: openChat()
            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: toolBar.bottom
        height: 2
        color: "#2B2E33"
    }
}
