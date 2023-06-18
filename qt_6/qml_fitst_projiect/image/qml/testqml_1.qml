import QtQuick
import QtQuick.Window

Window {
    id: window
    height: 400
    minimumHeight: 300
    minimumWidth: 300
    opacity: 0.9 //透明
    title: qsTr("testqml_1")
    visible: true
    width: 800
    x: -2200
    y: 800

    Text {
        id: text1
        color: "red"
        font.bold: true

        font.pointSize: 50
        text: "hello world"
        z: 1
    }
    Rectangle {
        id: rect1
        anchors.fill: parent
        color: "blue"

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            color: "green"
            height: 100
            width: 100
        }
        Rectangle {
            id: rect_1_2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin:10
            color: "grey"
            height: 100
            width: 100
        }
        Rectangle {
            rotation: 45//旋转45度
            transformOrigin: Item.TopLeft // 设置旋转为左上角中心点
            scale:0.8 //缩放
            anchors.horizontalCenter: rect_1_2.horizontalCenter
            anchors.top: rect_1_2.bottom
            anchors.topMargin:10
            color: "red"
            height: 100
            width: 100
        }
        MouseArea {
            height: rect1.height
            width: rect1.width

            onClicked: {
                text1.text = "hello";
                rect1.color = "brack";
            }
            onDoubleClicked: {
                rect1.color = "red";
            }
        }
    }
}

