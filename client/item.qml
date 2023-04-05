import QtQuick 2.14

Item {
    id: clientItem
    visible: true
    x: 10
    y: 20
    width: 200
    height: 208
    Component.onCompleted: {
        console.log(width)
    }
}
