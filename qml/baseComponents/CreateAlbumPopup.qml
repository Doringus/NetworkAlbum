import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Popup {
    id: popup

    signal created()

    property alias imageScale: slider.value
    property alias pathToAlbumText: pathToAlbumField.text
    property alias hasReserveFolder: toggleButton.checked
    property alias errorString: errorLabel.text
    property var albumLink: "TESTLINK"
    property url albumUrl: ""

    function popStackView() {
        stack.pop()
    }

    anchors.centerIn: parent
    width: 550
    height: 540
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    clip: true

    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        radius: 6
    }

    contentItem:  StackView {
        id: stack
        anchors.fill: parent
        initialItem: albumSettings
        popEnter: Transition{}
        popExit: Transition{}
    }

    onClosed: {
        imageScale = 50
        hasReserveFolder = false
        pathToAlbumText = ""
        albumUrl = ""
        stack.pop()
    }

    Item {
        id: albumSettings
        FileDialog {
            id: fileDialog
            title: "Выберите альбом"
            folder: shortcuts.pictures
            selectFolder: true
            onAccepted: {
                albumUrl = fileUrl
                var path = fileUrl.toString()
                path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/, "");
                pathToAlbumField.text = path
                pathToAlbumField.cursorPosition = 0
            }
        }
        Label {
           id: title
           anchors.top: parent.top
           anchors.topMargin: 15
           anchors.horizontalCenter: parent.horizontalCenter
           text: "Новый альбом"
           font.pointSize: 20
           color: "#40A7E3"
       }
       Label {
           id: pathToAlbumLabel
           anchors.top: title.bottom
           anchors.left: parent.left
           anchors.leftMargin: 20
           anchors.topMargin: 40
           text: "Путь к альбому"
           font.capitalization: Font.AllUppercase
           font.bold: true
           font.pointSize: 10
           color: "#87909C"
       }
       Column {
           anchors.top: pathToAlbumLabel.bottom
           anchors.left: pathToAlbumLabel.left
           anchors.right: parent.right
           anchors.rightMargin: 20
           anchors.topMargin: 10
           spacing: 25
           Column {
               anchors.left: parent.left
               anchors.right: parent.right
               spacing: 10
               RowLayout {
                   id: row
                   anchors.left: parent.left
                   anchors.right: parent.right
                   NTextField {
                       id: pathToAlbumField
                       Layout.preferredWidth: 320
                       text: pathToAlbumText
                       readOnly: true
                       hasError: errorString !==""
                   }
                   NButton {
                       width: 120
                       height: 40
                       text: "Обзор"
                       onClicked: fileDialog.open()
                   }
               }
               Label {
                   text: "Внимание папка с альбомом не должна сожержать подпапки"
                   font.pointSize: 10
                   color: "#FAA61A"
               }
               Label {
                   id: errorLabel
                   font.pointSize: 10
                   color: "#F04747"
                   visible: text !== ""
               }
           }

           Rectangle {
               anchors.left: parent.left
               anchors.right: parent.right
               height: 1
               color: "#EBEBEC"
           }
           Column {
               anchors.left: parent.left
               anchors.right: parent.right
               spacing: 10
               Label {
                   text: "Создать резервную папку"
                   font.capitalization: Font.AllUppercase
                   font.bold: true
                   font.pointSize: 10
                   color: "#87909C"
               }
               RowLayout {
                   anchors.left: parent.left
                   anchors.right: parent.right
                   Label {
                       text: "Эта настройка создаст копию оригинальной папки,\nпри синхронизации с клиентом"
                       font.pointSize: 10
                       color: "#87909C"
                   }
                   NToggleButton {
                        id: toggleButton
                        text: ""
                   }
               }
           }
           Rectangle {
               anchors.left: parent.left
               anchors.right: parent.right
               height: 1
               color: "#EBEBEC"
           }
           Column {
               anchors.left: parent.left
               anchors.right: parent.right
               spacing: 10
               Label {
                   text: "Сжатие изображений"
                   font.capitalization: Font.AllUppercase
                   font.bold: true
                   font.pointSize: 10
                   color: "#87909C"
               }
               NSlider {
                   id:slider
                   from: 1
                   to: 50
                   value: 50
               }
               Label {
                   text: "Размер изображений, переданных клиенту, будет меньше на " + slider.value.toFixed(1) + "%"
                   font.pointSize: 10
                   color: "#87909C"
               }
           }
           NButton {
               anchors.right: parent.right
               width: 120
               height: 40
               text: "Далее"
               onClicked: stack.push(albumCode)
           }
       }
   }


    Component {
        id: albumCode
        Item {
            Label {
                id: title
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Доступ"
                font.pointSize: 20
                color: "#40A7E3"
            }
            Column {
                anchors.top: title.bottom
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.topMargin: 40
                spacing: 20
                Label {
                    id: pathToAlbumLabel

                    text: "Ключ доступа"
                    font.capitalization: Font.AllUppercase
                    font.bold: true
                    font.pointSize: 10
                    color: "#87909C"
                }
                Label {
                    text: "Поделитесь данным приглашением"
                    font.pointSize: 10
                    wrapMode: "WrapAtWordBoundaryOrAnywhere"
                    color: "#87909C"
                }
                NCopyField {
                    width: 480
                    text: albumLink
                }
                Label {
                    text: "Внимание! Приглашение работает только для одного пользователя"
                    font.pointSize: 10
                    color: "#FAA61A"
                }
            }


            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: 75
                radius: 6
                color: "#F6F6F7"
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 40
                    anchors.rightMargin: 40
                    NButton {
                        text: "Назад"
                        onClicked: stack.pop()
                    }
                    NButton {
                        text: "Создать"
                        onClicked: {
                            popup.created()
                        }
                        Layout.alignment: Qt.AlignRight
                    }
                }
            }
        }
    }
}
