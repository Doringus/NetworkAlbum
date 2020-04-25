import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    width: 600
    height: 50

    property alias pageTitle: pageTitleLabel.text
    property alias showChat: showChatIndicator.isActivated

    signal backButtonClicked()
    signal openSettings()
    signal shareAlbum()
    signal openInExplorer()
    signal openChat()
    signal hideChat()

    Rectangle {
        id: componentTitle
        anchors.left: parent.left
        anchors.top: parent.top
        width: 240
        height: 50
        color: "#36393F"
        NToolButton {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            icon: "\uf060"
            onClicked: backButtonClicked()//parent.parent.parent.StackView.view.pop()
            toolTip: "Назад"
        }

        Label {
            id: pageTitleLabel
            anchors.fill: parent
            anchors.leftMargin: 20
            color: "white"
            text: "Новый альбом"
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
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            NToolButton {
                Layout.alignment: Qt.AlignLeft
                icon: "\uf07c"
                pointSize: 16
                toolTip: "Открыть в проводнике"
                onClicked: openInExplorer()
            }
            NToolButton {
                Layout.alignment: Qt.AlignLeft
                icon: "\uf1e0"
                pointSize: 16
                toolTip: "Поделиться"
                onClicked: shareAlbum()
            }
            ToolSeparator { }
            NToolButtonIndicator {
                id: showChatIndicator
                icon: "\uf0db"
                pointSize: 16
                toolTip: "Боковой чат"
                onActivated: {
                    openChat()
                }
                onDeactivated: {
                    hideChat()
                }
            }
            ToolSeparator { }
            NToolButton {
                icon: "\uf013"
                pointSize: 16
                toolTip: "Настройки"
                onClicked: openSettings()
            }
            NToolButton {
                icon: "\uf128"
                pointSize: 16
                toolTip: "Помощь"
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
