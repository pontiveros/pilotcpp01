import QtQuick
import QtMultimedia

Window {
    width: 600
    height: 600
    visible: true

    MediaPlayer {
        id: player
        // source: "file:////Users/pontiveros/Development/training/cpp/pilotcpp01/qtsample01/UsersBouncing.mp4"
        source: "./usersbouncing.mov"
        audioOutput: AudioOutput {}
        videoOutput: videoOutput
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
        anchors.margins: 10
    }

    Component.onCompleted: {
        player.play()
    }
}