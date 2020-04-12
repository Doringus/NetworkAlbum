import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import "../popups"
import NetworkAlbum 1.0

Page {
    header: NClientToolBar {
        pageTitle: ClientStore.folderName
        fileName: ClientStore.fileName
        backButtonVisible: ClientStore.albumUrl.toString().toLowerCase() !== ClientStore.currentFolderUrl.toString().toLowerCase()
        onBackButtonClicked: {
            if(ClientStore.albumUrl.toString().toLowerCase() !== ClientStore.currentFolderUrl) {
                ActionProvider.openFolder(folderModel.parentFolder)
            }
        }
        onMoveButtonClicked: {
            ActionProvider.showMovePopup()
        }
        onRenameButtonClicked: {
            ActionProvider.showRenamePopup()
        }
        onDeleteButtonClicked: {
            ActionProvider.deleteFiles()
        }
    }
    CreateFolderPopup {
        id: createFolderPopup
        errorString: ClientStore.errorString
        visible: ClientStore.showCreateFolderPopup
        onClicked: {
            ActionProvider.createFolder(folderName)
        }
        onAboutToHide: {
            ActionProvider.hideCreateFolderPopup()
        }
    }

    MovePopup {
        id: movePopup
        visible: ClientStore.showMovePopup
        onAboutToHide: {
            ActionProvider.hideMovePopup()
        }
    }

    RenamePopup {
        id: renamePopup
        fileName: ClientStore.fileName
        visible: ClientStore.showRenamePopup
        errorString: ClientStore.errorString
        onClicked: {
            ActionProvider.renameFile(fileName)
        }
        onAboutToHide: {
            ActionProvider.hideRenamePopup()
        }
    }

    Popup {
        id: imageViewPopup
        width: height * 1.7
        height: parent.height - 200
        anchors.centerIn: parent
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        contentItem: Image {
            anchors.fill: parent
         //   source: MainStore.imageUrl
            sourceSize.width: width
            sourceSize.height: height
            asynchronous: true
        }
      //  visible: MainStore.showImagePopup
     //   onAboutToHide: ActionProvider.hideImagePopup()
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
            id: scrollView
            anchors.left: parent.left
            anchors.right: chatRect.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            contentHeight: root.scrollViewContentHeight
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

            MouseArea {
                id: rootArea
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: scrollView.height
                onClicked: {
                    ActionProvider.deselectFiles()
                    gridImages.deselectAll()
                    gridFolders.deselectAll()
                }
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
                    folder: ClientStore.currentFolderUrl
                    rootFolder: ClientStore.albumUrl
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
                        onClicked: createFolderPopup.open()
                    }
                }

                delegate: FolderListItem {
                    objectName: "folderDelegate"
                    folderName: model.fileBaseName
                    onClicked: {
                        gridFolders.deselectAll()
                        gridImages.deselectAll()
                        selected = true
                        ActionProvider.clearAllAndSelectFile(model.fileURL)
                    }
                    onDoubleClicked: {
                        ActionProvider.openFolder(model.fileURL)
                    }
                    onCtrlClicked: {
                        if(!selected){
                            selected = true
                            ActionProvider.selectFile(model.fileURL)
                        } else {
                            selected = false
                            ActionProvider.deselectFile(model.fileURL)
                        }
                    }
                }
                function deselectAll() {
                    for(var i = 0; i < contentItem.children.length; ++i) {
                        var item = contentItem.children[i];
                        if (item.objectName === "folderDelegate") {
                            item.selected = false
                        }
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
                model:FolderListModel {
                    showDirs: false
                    folder: ClientStore.currentFolderUrl
                    rootFolder: ClientStore.albumUrl
                }
                cellHeight: 220
                cellWidth: 220
                delegate: ImageListItem {
                    objectName: "imageDelegate"
                    imagePath: model.fileURL
                    onImagePathChanged: {
                        imagePath = model.fileURL
                    }

                    imageName: model.fileName
                    onClicked: {
                        gridFolders.deselectAll()
                        gridImages.deselectAll()
                        selected = true
                        ActionProvider.clearAllAndSelectFile(imagePath)
                    }
                    onDoubleClicked: {
                        ActionProvider.openImagePopup(imagePath)
                    }
                    onCtrlClicked: {
                        if(!selected){
                            selected = true
                            ActionProvider.selectFile(imagePath)
                        } else {
                            selected = false
                            ActionProvider.deselectFile(imagePath)
                        }
                    }
                }
                function deselectAll() {
                    for(var i = 0; i < contentItem.children.length; ++i) {
                        var item = contentItem.children[i];
                        if (item.objectName === "imageDelegate") {
                            item.selected = false
                        }
                    }
                }
            }
        }
    }
}


