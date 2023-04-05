import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Item {
        id: myRectangle
        width: 100;
        height: 100;
        //color: "steelblue"
        anchors {
            top: parent.top
        }}
}
