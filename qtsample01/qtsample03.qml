import QtQuick
import QtMultimedia

Window {
    width: 600
    height: 600
    visible: true

    MediaPlayer {
        id: player
        source: "./usersbouncing.mov"
        audioOutput: AudioOutput {}
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
}
