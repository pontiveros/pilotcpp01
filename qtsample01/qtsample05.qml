import QtQuick.Window 2.2
import QtQuick.Controls 2.12
// import QtMultimedia 5.15 // for linux arm64
import QtMultimedia

ApplicationWindow {
    id: mainWindow
    width: 1024
    height: 600
    visible: true

    Button {
        text: "Open Modal"
        onClicked: modalPopup.open()
    }

    Popup {
        id: modalPopup
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Rectangle {
            width: parent.width
            height: parent.height
            color: "lightblue"
            MediaPlayer {
                id: player
                source: "./video-02.mov"
                videoOutput: videoOutput
                loops: MediaPlayer.Infinite
            }

            VideoOutput {
                id: videoOutput
                anchors.fill: parent
                anchors.margins: 10
            }

            Component.onCompleted: {
                player.play()
            }

            Button {
                x: 0
                y: 0
                // anchors.centerIn: parent
                text: "Close Modal"
                onClicked: modalPopup.close()
            }
        }
    }

}