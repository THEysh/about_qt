import QtQuick
import QtQuick.Window

Window {
    id: window
    property int index: 1

    height: 480
    minimumHeight: 300
    minimumWidth: 300
    opacity: 1 //闂侇偄绻戝Σ鎴炴償閿燂拷
    title: qsTr("testqml_1")
    visible: true
    width: 720
    x: -2200
    y: 700

    Image {
        id: img
        anchors.fill: parent
        source: "qrc:img/" + index + ".jpg"
    }
    Rectangle {
        id: leftbtn
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        color: "#FFFFFF"
        height: 200
        opacity: 0.5 //闂侇偄绻戝Σ鎴炴償閿燂拷
        radius: 10
        width: 40

        Text {
            id: text_leftbtn
            anchors.centerIn: parent
            color: "#000000"
            font.bold: true
            font.pointSize: 20
            text: "<"
        }
        MouseArea {
            anchors.fill: parent

            onClicked: {
                if (index === 1) {
                    index = 2;
                } else {
                    index = 1;
                }
                parent.color = "#FFFFFF";
                text_leftbtn.color = "#000000";
            }
            onPressed: {
                parent.color = "#000000";
                text_leftbtn.color = "#FFFFFF";
            }
        }
    }
    Rectangle {
        id: rightbtn
        anchors.right: parent.right
        anchors.rightMargin: leftbtn.rightMargin
        anchors.verticalCenter: parent.verticalCenter
        height: leftbtn.height
        opacity: leftbtn.opacity //闂侇偄绻戝Σ鎴炴償閿燂拷
        radius: leftbtn.radius
        width: leftbtn.width

        Text {
            id: text_rightbtn
            anchors.centerIn: parent
            color: "#000000"
            font.bold: true
            font.family: "鐎甸偊鍠涢拏瀣⒖閸涘鎷�"
            font.pointSize: 20
            text: ">"
        }
        MouseArea {
            anchors.fill: parent

            onClicked: {
                if (index === 1) {
                    index = 2;
                } else {
                    index = 1;
                }
                parent.color = "#FFFFFF";
                text_rightbtn.color = "#000000";
            }
            onPressed: {
                parent.color = "#000000";
                text_rightbtn.color = "#FFFFFF";
            }
        }
    }
}
