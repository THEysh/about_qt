import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    height: 480
    title: "Hello World"
    visible: true
    width: 640

    Text {
        anchors.centerIn: parent
        text: qsTr("Hello World!")
    }
}
