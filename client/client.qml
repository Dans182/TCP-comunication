import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    id: clientWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        id: myText
        text: "Mi texto"
        x: pos_x
        y: pos_y
    }

    //    Rectangle {
    //        width: 340
    //        height: 340
    //        color: "steelblue"
    //        Component.onCompleted: {
    //            console.log(width)
    //        }
    //        anchors {
    //            top: parent.top
    //        }
    //    }
}



