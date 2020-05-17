import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import "../popups"
import NetworkAlbum 1.0


Page {

    signal back()

    NToolButton {
        anchors.left: parent.left
        anchors.leftMargin: 10
        icon: "\uf060"
        iconColor: "#87909C"
        toolTip: "Назад"
        height: 50
        onClicked: {
            if(AlbumStore.albumUrl.toString().toLowerCase() !== folderModel.folder.toString().toLowerCase()) {
                ActionProvider.changeMoveDir(folderModel.parentFolder)
            } else {
                back()
            }
        }
    }
    Label {
        id: folderLabel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 50
        height: 50
        text: ChangesStore.currentMoveFolderName
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 20
        color: "#87909C"
    }
    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: folderLabel.bottom
        height: 1
        color: "#EBEBEC"
    }
    ListView {
        id: foldersList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: folderLabel.bottom
        anchors.topMargin: 1
        anchors.bottom: bottomRect.top
        clip: true
        interactive: true
        boundsBehavior: Flickable.StopAtBounds
        currentIndex: -1
        model: FolderListModel {
            id: folderModel
            showDirs: true
            showFiles: false
            rootFolder: AlbumStore.albumUrl
            folder: ChangesStore.currentMoveFolder
            Component.onCompleted: {
                console.log(AlbumStore.albumUrl, ChangesStore.currentMoveFolder)
            }
        }

        ScrollBar.vertical: ScrollBar {}
        delegate: NFolderItem {
            height: 40
            width: parent.width
            selected: index === foldersList.currentIndex
            onClicked: foldersList.currentIndex = index
            folderName: model.fileName
            folderPath: model.fileURL
            onChdir: {
                ActionProvider.changeMoveDir(model.fileURL)
            }
        }
    }
    Rectangle {
        id: bottomRect
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 60
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 1
            color: "#EBEBEC"
        }
        RowLayout {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            anchors.bottomMargin: 10
            Label {
                id: errorLabel
                Layout.alignment: Qt.AlignLeft
                font.pointSize: 10
                color: "#F04747"
                text: ChangesStore.errorString
                visible: text !== ""
            }
            NButton {
                Layout.alignment: Qt.AlignRight
                text: "Переместить"
                onClicked: {
                    if(folderModel.count == 0 || foldersList.currentIndex == -1) {
                        ActionProvider.moveFiles(folderModel.folder)
                    } else {
                        ActionProvider.moveFiles(folderModel.get(foldersList.currentIndex, "fileURL"))
                    }
                }
            }
        }
    }
}
