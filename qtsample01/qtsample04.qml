import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    Rectangle {
        width: parent.width
        height: parent.height

        Button {
            text: "Show Full-Screen Modal"
            onClicked: {
                // Show the modal view in full screen
                var modalView = Qt.createQmlObject('import QtQuick 2.15; Rectangle { color: "lightblue"; width: parent.width; height: parent.height; Button { text: "Close View" onClicked: { this.visible = false; } } }', parent, "modalView");
                modalView.visible = true;
            }
        }
    }
}