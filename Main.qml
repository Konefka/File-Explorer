import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window

    visible: true
    width: 1100
    height: 600
    minimumWidth: 550
    minimumHeight: 300

    title: "File Explorer"
    flags: Qt.platform.os === "windows"
        ? Qt.FramelessWindowHint | Qt.Window
        : Qt.Window

    // property bool lightMode: Application.styleHints.colorScheme === Qt.Light
    // property color reallyDark: "#1f1f1f"
    // property color dark: "#262626"
    // property color reallyLight: "#e7e7e7"
    // property color light: "#e0e0e0"

    Loader {
        id: titleBarLoader
        active: Qt.platform.os === "windows"

        anchors.top: parent.top
        width: parent.width
        height: active ? 35 : 0

        sourceComponent: windowsTitleBar
    }

    Component {
        id: windowsTitleBar

        Rectangle {
            anchors.fill: parent

            color: "#202020"

            Image {
                anchors.left: parent.left
                anchors.leftMargin: 12
                anchors.verticalCenter: parent.verticalCenter

                width: 22
                height: 22

                source: "img/icon.png"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                anchors {
                    left: parent.left
                    leftMargin: 42
                    verticalCenter: parent.verticalCenter
                }

                text: "File Explorer"

                color: "#ffffff"
                font.pixelSize: 14
            }

            MouseArea {
                anchors.fill: parent

                onPressed: {
                    window.startSystemMove()
                }
            }

            Row {
                id: buttons

                anchors {
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }

                Rectangle {
                    width: 46
                    height: parent.height

                    color: minimizeMouse.containsMouse ? "#3a3a3a" : "transparent"

                    Image {
                        anchors.centerIn: parent

                        source: "img/minimize.svg"
                        width: 12
                        height: 12
                    }

                    MouseArea {
                        id: minimizeMouse

                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: window.showMinimized()
                    }
                }

                Rectangle {
                    width: 46
                    height: parent.height

                    color: maximizeMouse.containsMouse ? "#3a3a3a" : "transparent"

                    Image {
                        anchors.centerIn: parent

                        source: "img/maximize.svg"
                        width: 20
                        height: 20
                    }

                    MouseArea {
                        id: maximizeMouse

                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            if (window.visibility === Window.Maximized)
                                window.showNormal()
                            else
                                window.showMaximized()
                        }
                    }
                }

                Rectangle {
                    width: 46
                    height: parent.height

                    color: closeMouse.containsMouse ? "#c42b1c" : "transparent"

                    Image {
                        anchors.centerIn: parent

                        source: "img/close.svg"
                        width: 16
                        height: 16
                    }

                    MouseArea {
                        id: closeMouse

                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: Qt.quit()
                    }
                }
            }
        }
    }

    Rectangle {
        id: currentDirBox

        anchors {
            top: titleBarLoader.bottom
            left: parent.left
            right: parent.right
        }

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
                    width: 24
                    height: 24

                    source: isDirectory
                        ? "img/folder.svg"
                        : "img/file.svg"

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