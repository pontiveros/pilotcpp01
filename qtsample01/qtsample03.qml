import QtQuick 2.5
// import QtMultimedia 5.15
import QtMultimedia

Rectangle {
    width: 1024
    height: 600
    visible: true

    MediaPlayer {
        id: player
        source: "./video-01.mov"
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
