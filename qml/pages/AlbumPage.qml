import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import NetworkAlbum 1.0

Page {
    header: NToolBar {
        pageTitle: MainStore.albumPageTitle
        onBackButtonClicked: {
            if(MainStore.albumUrl.toString().toLowerCase() === folderModel.folder.toString().toLowerCase()) {
                parent.StackView.view.pop()
            } else {
                ActionProvider.openFolder(folderModel.parentFolder)
            }
        }
    }
    property var imagesModel

    Popup {
        id: imageViewPopup
        width: height * 1.7
        height: parent.height - 200
        anchors.centerIn: parent
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        contentItem: Image {
            anchors.fill: parent
            source: MainStore.imageUrl
            sourceSize.width: width
            sourceSize.height: height
            asynchronous: true
        }
        visible: MainStore.showImagePopup
        onAboutToHide: ActionProvider.hideImagePopup()
    }

    Item {
        id: root
        anchors.fill: parent
        property int scrollViewContentHeight: folderText.height + gridFolders.height +
                                              imagesText.height + gridImages.height +
                                              folderText.anchors.topMargin + gridFolders.anchors.topMargin +
                                              imagesText.anchors.topMargin + gridImages.anchors.topMargin + 10

        Rectangle {
            anchors.fill: parent
            color: "#2F3136"
        }

        Rectangle {
            id: chatRect
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 350
            color: "#36393F"
            NChat {
                anchors.fill: parent
            }
        }
        ScrollView {
            anchors.left: parent.left
            anchors.right: chatRect.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            contentHeight:root.scrollViewContentHeight
            ScrollBar.vertical: ScrollBar {
                orientation: Qt.Vertical
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                active: true
                contentItem: Rectangle {
                    radius: width / 2
                    implicitWidth: 6
                    color: "#9A9A9C"
                }
                width: 10
                z:2
            }

            Text {
                id: folderText
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 30
                anchors.leftMargin: 58
                color: "white"
                text: "Папки"
                font.weight: Font.Bold
                font.pointSize: 12
                font.capitalization: Font.AllUppercase
            }
            GridView {
                id: gridFolders
                anchors.left: folderText.left
                anchors.right: parent.right
                anchors.top: folderText.bottom
                anchors.topMargin: 20
                height: Math.ceil(model.count / Math.floor(width / cellWidth)) * cellHeight + 80
                interactive: false
                boundsBehavior: Flickable.StopAtBounds
                flow: GridView.LeftToRight
                snapMode: GridView.SnapToRow
                cacheBuffer: 0
                model: FolderListModel {
                    id: folderModel
                    showDirs: true
                    showFiles: false
                    folder: MainStore.currentFolderUrl
                    rootFolder: MainStore.albumUrl                    
                }
                cellHeight: 60
                cellWidth: 220
                header: Rectangle {
                    width: 200
                    height: 80
                    color: "transparent"
                    FolderListItem {
                        anchors.verticalCenter: parent.verticalCenter
                        folderName: "Создать"
                        folderIcon: "\uf067"
                    }
                }

                delegate: FolderListItem {
                    folderName: model.fileBaseName
                    onClicked: {
                        ActionProvider.openFolder(folderModel.get(index, "fileURL"))
                    }
                }
            }
            Text {
                id: imagesText
                anchors.top: gridFolders.bottom
                anchors.left: gridFolders.left
                anchors.topMargin: 20
                color: "white"
                text: "Изображения"
                font.weight: Font.Bold
                font.pointSize: 12
                font.capitalization: Font.AllUppercase
            }

            GridView {
                id: gridImages
                anchors.left: imagesText.left
                anchors.right: parent.right
                anchors.top: imagesText.bottom
                anchors.topMargin: 20
                height: Math.ceil(model.count / Math.floor(width / cellWidth)) * cellHeight
                interactive: false
                boundsBehavior: Flickable.StopAtBounds
                flow: GridView.LeftToRight
                snapMode: GridView.SnapToRow
                cacheBuffer: 0
                model: FolderListModel {
                    showDirs: false
                    folder: MainStore.currentFolderUrl
                    rootFolder: MainStore.albumUrl
                }
                cellHeight: 220
                cellWidth: 220
                delegate: ImageListItem {
                    imagePath: model.fileURL
                    imageName: model.fileBaseName
                    onClicked: {
                        ActionProvider.openImagePopup(imagePath)
                    }
                }
            }
        }
    }
}


