import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    visible: true
    width: 1100
    height: 600
    minimumWidth: 550
    minimumHeight: 300
    title: qsTr("File Explorer")
    // property bool lightMode: Application.styleHints.colorScheme === Qt.Light
    // property color reallyDark: "#1f1f1f"
    // property color dark: "#262626"
    // property color reallyLight: "#e7e7e7"
    // property color light: "#e0e0e0"

    Rectangle {
        id: currentDirBox
        width: parent.width
        height: 50
        clip: true

        TextField {
            id: currentDirText

            anchors.fill: parent
            anchors.margins: 10

            leftPadding: 5
            rightPadding: 5
            topPadding: 2
            bottomPadding: 2

            verticalAlignment: Text.AlignVCenter
            placeholderText: "Where do you wanna go?"
            text: fileSystemModel
                  ? fileSystemModel.currentPath
                  : ""
            font.pixelSize: 18

            onAccepted: {
                fileSystemModel.changePath(text)
            }
        }
    }

    ListView {
        id: dirList

        anchors {
            top: currentDirBox.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        clip: true

        model: fileSystemModel
        spacing: 2

        delegate: Button {
            width: 200
            height: 28

            clip: true

            Row {
                anchors {
                    left: parent.left
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }

                spacing: 2

                Image {
                    id: dirImg
                    width: 36
                    height: 36

                    source: isDirectory
                        ? "img/folder.png"
                        : "img/txt_file.png"

                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    width: parent.width - dirImg.width
                    height: parent.height

                    text: name
                    font.pixelSize: 12

                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    maximumLineCount: 1
                }
            }
            onClicked: {
                if (isDirectory) {
                    fileSystemModel.changePath(path);
                } else {
                    fileSystemModel.openItem(path);
                }
            }
        }
    }
}