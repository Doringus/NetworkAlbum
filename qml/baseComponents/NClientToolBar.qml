import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    width: 600
    height: 50

    property alias pageTitle: pageTitleLabel.text
    property alias backButtonVisible: backButton.visible
    property alias fileName: fileNameLabel.text

    signal backButtonClicked()
    signal moveButtonClicked()
    signal renameButtonClicked()
    signal sendImagesButtonClicked()
    signal openInExplorer()
    signal openChat()
    signal hideChat()
    signal deleteButtonClicked()

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
            onClicked: backButtonClicked()//parent.parent.parent.StackView.view.pop()
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
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: sideButtons.left
            anchors.rightMargin: 20
            spacing: 0
            ToolSeparator { }
            Label {
                id: fileNameLabel
                color: "white"
                text: "Файл"
                elide: "ElideRight"
                Layout.preferredWidth: 280
                font.weight: Font.DemiBold
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pointSize: 16
            }
            RowLayout {
                visible: fileName != ""
                NToolButton {
                    icon: "\uf1f8"
                    pointSize: 16
                    toolTip: "Удалить"
                    onClicked: {
                        deleteButtonClicked()
                    }
                }
                NToolButton {
                    icon: "\uf0ec"
                    pointSize: 16
                    toolTip: "Переместить"
                    onClicked: {
                        moveButtonClicked()
                    }
                }
                NToolButton {
                    icon: "\uf040"
                    pointSize: 16
                    toolTip: "Переименовать"
                    onClicked: {
                        renameButtonClicked()
                    }
                }
            }
        }

        RowLayout {
            id: sideButtons
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20

            NToolButton {
                icon: "\uf093"
                pointSize: 16
                toolTip: "Отправить изменения"
                onClicked: {
                    sendImagesButtonClicked()
                }
            }
            NToolButton {
                icon: "\uf07c"
                pointSize: 16
                toolTip: "Открыть папку альбома"
                onClicked: {
                    openInExplorer()
                }
            }
            ToolSeparator { }
            NToolButtonIndicator {
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
