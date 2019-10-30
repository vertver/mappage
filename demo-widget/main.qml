/*
  Use C++ model as a source of polyline data.
  */
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtLocation 5.6
import QtPositioning 5.6
import QtGraphicalEffects 1.0

import Polyline 1.0
import QtQuick.Window 2.0

Window {
    id: root
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
