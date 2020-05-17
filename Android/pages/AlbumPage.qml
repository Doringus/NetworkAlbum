import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import "../popups"
import NetworkAlbum 1.0

Page {
    id: page
    signal openMove()
    signal openChat()
    signal openAbout()
    signal openImage()

    header: NClientToolBar {
        pageTitle: AlbumStore.albumPageTitle
        backButtonVisible: AlbumStore.albumUrl.toString().toLowerCase() !== AlbumStore.currentFolderUrl.toString().toLowerCase()
        onBackButtonClicked: {
            if(AlbumStore.albumUrl.toString().toLowerCase() !== AlbumStore.currentFolderUrl) {
                ActionProvider.openFolder(folderModel.parentFolder)
                ActionProvider.deselectFiles()
            }
        }
        onCreateFolder: {
            ActionProvider.showCreateFolderPopup()
        }
        onOpenChat: {
            page.openChat()
        }
        onOpenHelp: {
            page.openAbout()
        }
        onSendImagesButtonClicked: ActionProvider.syncImages()
    }
    Item {
        id: root

        property int scrollViewContentHeight: folderText.height + gridFolders.height +
                                              imagesText.height + gridImages.height +
                                              folderText.anchors.topMargin + gridFolders.anchors.topMargin +
                                              imagesText.anchors.topMargin + gridImages.anchors.topMargin + 10

        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "#2F3136"
        }

        MultipleMenuPopup {
            id: multipleMenu
            z:2
            width: parent.width - 30
            height: 80
            y: parent.height - 130
            x: 15
            files: ChangesStore.fileName
            onOpenMove: {
                page.openMove()
            }
            onClearSelected: {
                gridFolders.deselectAll()
                gridImages.deselectAll()
                ActionProvider.deselectFiles()
            }
            visible: {
                ChangesStore.fileName != "" && !folderMenu.visible && !imageMenu.visible
            }
        }

        RenamePopup {
            id: renamePopup
            width: root.width * 5 / 6
            height: root.height * 2 / 3
            fileName: ChangesStore.fileName
            visible: ChangesStore.showRenamePopup
            errorString: ChangesStore.errorString
            onClicked: {
                ActionProvider.renameFile(fileName)
                gridFolders.deselectAll()
                gridImages.deselectAll()
            }
            onAboutToHide: {
                ActionProvider.hideRenamePopup()
            }
        }

        CreateFolderPopup {
            id: createFolderPopup
            width: root.width - 20
            height: root.height * 2 / 3
            errorString: ChangesStore.errorString
            visible: ChangesStore.showCreateFolderPopup
            onClicked: {
                ActionProvider.createFolder(folderName)
            }
            onAboutToHide: {
                ActionProvider.hideCreateFolderPopup()
            }
        }

        Menu {
            id: folderMenu
            y: root.height - height
            x: 0
            width: root.width
            topPadding: 35

            property bool startedAction: false

            Action { text: qsTr("Переместить"); icon.name: "\uf0ec"; onTriggered: {
                    folderMenu.startedAction = true
                    openMove()}
            }
            Action { text: qsTr("Переименовать"); icon.name: "\uf040"; onTriggered: {
                    folderMenu.startedAction = true
                    ActionProvider.showRenamePopup();}}
            Action { text: qsTr("Удалить"); icon.name: "\uf1f8"; onTriggered:  ActionProvider.deleteFiles()}

            onOpened: startedAction = false;
            onAboutToHide: {
                if(!startedAction) {
                    ActionProvider.deselectFiles()
                    gridFolders.deselectAll()
                    gridImages.deselectAll()
                }


            }

            delegate: NMenuItem{}
            background: Rectangle {
                Label {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    anchors.topMargin: 10
                    font.pointSize: 12
                    color: "white"
                    text: ChangesStore.fileName
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                }

                implicitWidth: 210
                color: "#18191C"
                radius: 4
            }

        }
        Menu {
            id: imageMenu
            y: root.height - height
            x: 0
            width: root.width
            topPadding: 30
            property bool startedAction: false
            onOpened: startedAction = false
            onAboutToHide: {
                if(!startedAction) {
                    ActionProvider.deselectFiles()
                    gridImages.deselectAll()
                    gridFolders.deselectAll()
                }
            }
            Action { text: qsTr("Переместить"); icon.name: "\uf0ec"; onTriggered:{
                    imageMenu.startedAction = true
                    openMove()
                }}
            Action { text: qsTr("Переименовать"); icon.name: "\uf040"; onTriggered: {
                    imageMenu.startedAction = true
                    ActionProvider.showRenamePopup()}
            }
            delegate: NMenuItem{}
            background: Rectangle {
                Label {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    anchors.topMargin: 10
                    font.pointSize: 12
                    color: "white"
                    text: ChangesStore.fileName
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                }
                implicitWidth: 210
                color: "#18191C"
                radius: 4
            }

        }
        Menu {
            id: applicationMenu
            y: root.height - height
            x: 0
            width: root.width
            topPadding: 10

            Action { text: qsTr("Открыть"); icon.name: "\uf07c"; onTriggered: root.clicked()}
            Action { text: qsTr("Открыть резервную папку"); icon.name: "\uf115"; onTriggered:  root.showReserve();}
            Action { text: qsTr("Копировать ссылку"); icon.name: "\uf064"; onTriggered:  root.showLink()}
            Action { text: qsTr("Закрыть альбом"); icon.name: "\uf00d"; onTriggered: root.closeAlbum()}

            delegate: NMenuItem{}
            background: Rectangle {
                implicitWidth: 210
                color: "#18191C"
                radius: 4
            }

        }


        ScrollView {
            anchors.fill: parent
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
                boundsBehavior: Flickable.StopAtBounds
                flow: GridView.LeftToRight
                snapMode: GridView.SnapToRow
                cacheBuffer: 0
                model: FolderListModel {
                    id: folderModel
                    showDirs: true
                    showFiles: false
                    folder: AlbumStore.currentFolderUrl
                    rootFolder: AlbumStore.albumUrl
                }
                cellHeight: 60
                cellWidth: (gridFolders.width - 20) / 2
                delegate: FolderListItem {
                    width: gridFolders.cellWidth - 10
                    folderName: model.fileBaseName
                    onClicked: {
                        ActionProvider.openFolder(folderModel.get(index, "fileURL"))
                    }
                    onMenuClicked: {
                        gridFolders.deselectAll()
                        folderMenu.open()
                        selected = true
                        ActionProvider.clearAllAndSelectFile(model.fileURL)
                    }
                    onPressAndHold: {
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
                anchors.topMargin: 10
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
                    folder: AlbumStore.currentFolderUrl
                    rootFolder: AlbumStore.albumUrl
                    nameFilters: [ "*.png", "*.jpg" ]
                }
                cellHeight: 220
                cellWidth: (gridImages.width - 20) / 2
                delegate: ImageListItem {
                    width: gridImages.cellWidth - 10
                    objectName: "imageDelegate"
                    imagePath: model.fileURL
                    imageName: model.fileName
                    onMenuClicked: {
                        gridImages.deselectAll()
                        imageMenu.open()
                        ActionProvider.clearAllAndSelectFile(model.fileURL)
                    }
                    onClicked: {
                        ActionProvider.openImagePopup(model.fileURL)
                        page.openImage()
                        console.log("CLICKEDE")
                    }
                    onPressAndHold: {
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
                        if (item.objectName === "imageDelegate") {
                            item.selected = false
                        }
                    }
                }
            }

        }
    }
}
