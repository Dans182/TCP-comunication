import QtQuick 2.14
import QtQuick.Controls 2.14

ApplicationWindow {
    id: clientWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        id: myText
        text: "Mi texto"
        x: 0
        y: 0
    }
}



