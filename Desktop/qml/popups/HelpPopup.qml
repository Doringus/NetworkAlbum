import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: root

    anchors.centerIn: parent
    width: 500
    height: 600

    modal: true
    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        color: "#36393F"
        radius: 6
    }
    contentItem: Rectangle {
        anchors.fill: parent
        color: "#36393F"
        radius: 6

        Rectangle {
            id: header
            height: 40
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 20
            color: "transparent"
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                Label {
                    font.pointSize: 18
                    color: "white"
                    text: "О программе"
                }
                NToolButton {
                    Layout.alignment: Qt.AlignRight
                    icon: "\uf00d"
                    toolTip: "Закрыть"
                    pointSize: 16
                    onClicked: root.close()
                }
            }
        }
        ScrollView {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: header.bottom
            anchors.bottom: footer.top
            anchors.topMargin: 20
            anchors.bottomMargin: 20
            clip: true
            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 20
                spacing: 20
                Label {
                    color: "#3E8466"
                    text: "Функции"
                    font.pointSize: 14
                    font.capitalization: Font.AllUppercase
                }
                Column {
                    spacing: 10
                    Label {
                        color: "white"
                        font.pointSize: 12
                        text: "- Создавайте альбомы и делитесь фотографиями с друзьями"
                    }
                    Label {
                        color: "white"
                        font.pointSize: 12
                        text: "- Общайтесь"
                    }
                }
                Label {
                    color: "#3E8466"
                    text: "Советы для сервера"
                    font.pointSize: 14
                    font.capitalization: Font.AllUppercase
                }
                Column {
                    spacing: 10
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        font.pointSize: 12
                        text: "- При синхронизации изменений клиентом, у альбома появится восклицательный знак"
                        wrapMode: Text.WordWrap
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        font.pointSize: 12
                        text: "- Будьте осторожны при закрытии альбома: к нему может быть подключен клиент"
                        wrapMode: Text.WordWrap
                    }
                }

                Label {
                    color: "#3E8466"
                    text: "Советы для клиента"
                    font.pointSize: 14
                    font.capitalization: Font.AllUppercase
                }
                Column {
                    spacing: 10
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        font.pointSize: 12
                        text: "- Удалять можно только пустые папки"
                        wrapMode: Text.WordWrap
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        font.pointSize: 12
                        text: "- Чтобы выделить несколько файлов зажмите ctrl"
                        wrapMode: Text.WordWrap
                    }
                }

                Label {
                    color: "#3E8466"
                    text: "И еще кое-что"
                    font.pointSize: 14
                    font.capitalization: Font.AllUppercase
                }
                Column {
                    spacing: 10
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        font.pointSize: 12
                        text: "- Есть вопросы, предложения - пишите на почту kekenken3120@gmail.com"
                        wrapMode: Text.WordWrap
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        font.pointSize: 12
                        text: "- Попробуйте найти пасхалку. Подсказка: through the gates of hell.... Что бы это значило?"
                        wrapMode: Text.WordWrap
                    }
                }

            }
        }

        Rectangle {
            id: footer
            color: "#2F3136"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 60
            Label {
                anchors.fill: parent
                color:"#B8B9BB"
                text: "ver. 1.0"
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

    }

}
