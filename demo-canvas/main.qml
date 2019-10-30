/*
  Use C++ model as a source of polyline data.
  */
import QtQuick 2.9
import QtQuick.Window 2.0

Window {
    id: root
//    minimumWidth: 900
//    minimumHeight: 540
    width: 900
    height: 540
    visible: true
    title: "Map"

    MapPage {
        id: mapPage
        anchors.fill: parent
        visible: true
        screenWidth: root.Screen.width
        screenHeight: root.Screen.height
    }
}
