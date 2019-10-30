// MapPage
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtLocation 5.6
import QtPositioning 5.6
import QtGraphicalEffects 1.0

import Polyline 1.0

import "utils.js" as Utils

Rectangle {
    id: root
    anchors.fill: parent
    color: "transparent"

    property int screenWidth: 0
    property int screenHeight: 0

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    PolylineModel {
        id: polylineModel
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(55.7661, 37.5324) // SDL office
        //center: QtPositioning.coordinate(60, -180)
        zoomLevel: 5
        copyrightsVisible: false

        property real prevPaintLon: 0

        Component.onCompleted: {
            console.debug("map.onCompleted", root.screenWidth, root.screenHeight)
            tracksCanvasRect.x = -root.screenWidth
            tracksCanvasRect.y = -root.screenHeight
            tracksCanvasRect.width = root.screenWidth * 3
            tracksCanvasRect.height = root.screenHeight * 3
        }

        onZoomLevelChanged: {
            tracksCanvas.requestPaint()
        }

        onCenterChanged: {
            console.debug("map.onCenterChanged", center.longitude, center.latitude)
            const vr = map.visibleRegion
            if (!vr.isValid)
                return

            var vgr = Utils.rectFromMapVisibleRegion(vr)

            const cgr = tracksCanvasRect.geoRect

            if (cgr.width >= 360) {
                console.debug("map.onCenterChanged **** cgr.width >= 360:", cgr.width)
//                console.debug("map.onCenterChanged", "vgr", "bottom_left", vgr.x, vgr.y, "size", vgr.width, vgr.height)
//                console.debug("map.onCenterChanged", "cgr", "bottom_left", cgr.x, cgr.y, "size", cgr.width, cgr.height)

                // TODO
                // сейчас workaround
                // перерисовка по скроллу, чтобы исправлять косяки скролла
                // непонятно как сделать враппинг по нормальному, без перерисовки

                var prev_lon = prevPaintLon
                var lon = center.longitude
                // переход через 180 меридиан
                if (lon > 160 && prev_lon < -160) {
                    prev_lon += 360
                }
                else if(lon < -160 && prev_lon > 160) {
                    lon += 360
                }
                console.debug("map.onCenterChanged lon", lon, "prev_lon", prev_lon)

                const repaint_dlon =
                        /*zoomLevel < 3.2 ? 20 :
                        zoomLevel < 3.8 ? 30 :*/ 60

                if (!Utils.rectContains(cgr, vgr) || Math.abs(prev_lon - lon) > repaint_dlon) {
                    tracksCanvas.requestPaint()
                }
            }
            else {
                console.debug("map.onCenterChanged cgr.width < 720:", cgr.width)
//                console.debug("map.onCenterChanged", "vgr", "bottom_left", vgr.x, vgr.y, "size", vgr.width, vgr.height)
//                console.debug("map.onCenterChanged", "cgr", "bottom_left", cgr.x, cgr.y, "size", cgr.width, cgr.height)
                if (!Utils.rectContains(cgr, vgr)) {
                    tracksCanvas.requestPaint()
                }
            }
        }

        MapQuickItem {
            id: tracksMapItem
            anchorPoint.x: 0
            anchorPoint.y: 0
            sourceItem: Rectangle {
                id: tracksCanvasRect
                color: "transparent"
                border.color: "red"

                property rect geoRect

                Canvas {
                    id: tracksCanvas
                    anchors.fill: parent

                    onPaint: {
					
						gImGuiLines.Clear()
                        console.debug("tracksCanvas.onPaint", "--------------", map.zoomLevel)

                        map.prevPaintLon = map.center.longitude

                        const vgr0 = map.visibleRegion.boundingGeoRectangle()
                        tracksMapItem.coordinate = vgr0.topLeft
                        console.debug("tracksCanvas.onPaint set tracksMapItem.coordinate=", vgr0.topLeft.longitude)

                        // центральный квадрант канваса
                        var dlon = calculateCanvasGeoWidth(root.screenWidth)
                        console.debug("tracksCanvas.onPaint dlon", dlon)

                        //------------------------------------------------------
                        // нужны только широты
                        const cp1 = map.toCoordinate(Qt.point(0, 2*root.screenHeight - 1), false)
                        const cp2 = map.toCoordinate(Qt.point(0, -root.screenHeight), false)

                        // канвас выходит вверх за Северный полюс?
                        // при необходимости коррекция y-координаты канваса, чтобы она соответствовала Северному полюсу
                        const p_north = map.fromCoordinate(QtPositioning.coordinate(90, 0), false)
                        tracksCanvasRect.y = Math.max(p_north.y, -root.screenHeight)

                        if (dlon < 360) {
                            tracksCanvasRect.geoRect = Qt.rect(
                                        map.toCoordinate(Qt.point(0, 0), false).longitude + 540 - dlon,
                                        cp1.latitude,
                                        dlon * 3,
                                        cp2.latitude - cp1.latitude)
                        }
                        else {
                            tracksCanvasRect.geoRect = Qt.rect(0,
                                                         cp1.latitude,
                                                         1080,
                                                         cp2.latitude - cp1.latitude)
                        }

                        const cgr = tracksCanvasRect.geoRect
                        console.debug("tracksCanvas.onPaint set geoRect:",
                                      "bottom_left", cgr.x, cgr.y,
                                      "size", cgr.width, cgr.height)
                        //------------------------------------------------------

                        var ctx = tracksCanvas.getContext("2d")
                        ctx.clearRect(0, 0, tracksCanvasRect.width, tracksCanvasRect.height)
                        ctx.reset()
                        ctx.resetTransform()
                        ctx.save()

                        if (dlon < 120) {
                            paintTracks(ctx)
                        }
                        else {
                            paintTracksWrap(ctx)
                        }

                        ctx.restore()

                        console.debug("tracksCanvas.onPaint", "----------------------------------------------")
                    }

                    //----------------------------------------------------------
                    function calculateCanvasGeoWidth(pixel_width) {
                        var p1 = map.toCoordinate(Qt.point(0, 0), false)
                        var p2 = map.toCoordinate(Qt.point(99, 0), false)
                        if (p2.longitude < p1.longitude)
                            p2.longitude += 360
                        var dlon = (p2.longitude - p1.longitude) * (pixel_width / 100.)
                        console.assert(dlon > 0,
                                       "failed:" + dlon + "> 0; " + p2.longitude + " " + p1.longitude)
                        return dlon
                    }

                    //----------------------------------------------------------
                    function calculateGlobePixelWidth() {
                        var p1 = map.fromCoordinate(
                                    QtPositioning.coordinate(0, 0),
                                    false)
                        var p2 = map.fromCoordinate(
                                    QtPositioning.coordinate(0, 10),
                                    false)
                        if (p2.x < p1.x) {
                            p1 = p2
                            p2 = map.fromCoordinate(
                                        QtPositioning.coordinate(0, 20),
                                        false)
                        }
                        return (p2.x - p1.x) * 36
                    }

                    //----------------------------------------------------------
                    function paintTracks(ctx) {
                        const globe_width = calculateGlobePixelWidth()
                        const track_count = polylineModel.tracksSize()
                        ctx.lineWidth = 3
                        ctx.strokeStyle = "blue"
//                        ctx.globalAlpha = 0.5
                        ctx.beginPath()
                        for (var i = 0; i < track_count; ++i) {
                            paintTrack(ctx, i, globe_width)
                        }
                        ctx.stroke()
                    }

                    //----------------------------------------------------------
                    function paintTracksWrap(ctx) {
                        const globe_width = calculateGlobePixelWidth()
                        const track_count = polylineModel.tracksSize()
                        ctx.lineWidth = 3
                        ctx.strokeStyle = "blue"
//                        ctx.globalAlpha = 0.5
                        ctx.beginPath()
                        for (var i = 0; i < track_count; ++i) {
                            paintTrackWrap(ctx, i, globe_width)
                        }
                        ctx.stroke()
                    }

                    //----------------------------------------------------------
                    function paintTrackWrap(ctx, idx, globe_width) {
                        var colors = ["red", "green"]

                        var coord_arr = polylineModel.trackData(idx)

                        if (coord_arr.length < 4 || Utils.isOdd(coord_arr.length)) {
                            console.assert(false, coord_arr.length)
                            return
                        }

                        const dx = tracksCanvasRect.x
                        const dy = tracksCanvasRect.y

                        for (var k = 0, dx1 = -globe_width; k < 2; ++k, dx1 += globe_width) {
                            ctx.strokeStyle = colors[k]
                            ctx.beginPath()

                            var p = map.fromCoordinate(
                                        QtPositioning.coordinate(coord_arr[0], coord_arr[1]),
                                        false)
                            ctx.moveTo(p.x - dx + dx1, p.y - dy)

                            var prev_p = p
                            for(var i = 2; i < coord_arr.length; i += 2) {
                                p = map.fromCoordinate(
                                            QtPositioning.coordinate(coord_arr[i], coord_arr[i+1]),
                                            false)
                                if (Math.abs(prev_p.x - p.x) > globe_width / 2) {
                                    if (prev_p.x > p.x)
                                        p.x += globe_width
                                    else
                                        p.x -= globe_width
                                }

                                //ctx.lineTo(p.x - dx + dx1, p.y - dy)
								gImGuiLines.DrawLine(p.x - dx + dx1, p.y - dy)
                                prev_p = p
                            }

                            ctx.stroke()
                        }
                    }

                    //----------------------------------------------------------
                    function paintTrack(ctx, idx, globe_width) {
                        var coord_arr = polylineModel.trackData(idx)

                        if (coord_arr.length < 4 || Utils.isOdd(coord_arr.length)) {
                            console.assert(false, coord_arr.length)
                            return
                        }

                        const dx = tracksCanvasRect.x
                        const dy = tracksCanvasRect.y

                        var p = map.fromCoordinate(
                                    QtPositioning.coordinate(coord_arr[0], coord_arr[1]),
                                    false)
                        ctx.moveTo(p.x - dx, p.y - dy)

                        var prev_p = p
                        for(var i = 2; i < coord_arr.length; i += 2) {
                            p = map.fromCoordinate(
                                        QtPositioning.coordinate(coord_arr[i], coord_arr[i+1]),
                                        false)
                            if (Math.abs(prev_p.x - p.x) > globe_width / 2) {
                                if (prev_p.x > p.x)
                                    p.x += globe_width
                                else
                                    p.x -= globe_width
                            }

                            //ctx.lineTo(p.x - dx, p.y - dy)
                            gImGuiLines.DrawLine(p.x - dx, p.y - dy)

							prev_p = p
                        }
                    }

                } // Canvas
            } // Rectangle
        } // MapQuickItem
    }
}
