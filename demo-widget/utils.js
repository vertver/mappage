// utils.js

// swallow
function copy(obj) {
    if (null === obj || "object" != typeof obj) return obj;
    var copy = obj.constructor();
    for (var attr in obj) {
        if (obj.hasOwnProperty(attr)) copy[attr] = obj[attr];
    }
    return copy;
}

function coordToPoint(c) {
    return Qt.point(c.longitude, c.latitude)
}

function isEven(n) {
   return n % 2 == 0;
}

function isOdd(n) {
   return Math.abs(n % 2) == 1;
}

// r1 contains r2
function rectContains(r1, r2) {
//    if (r1.x > r2.x) {
////        console.debug("rectContains 1", r1.x, ">", r2.x)
//        return false;
//    }
//    if (r1.y > r2.y) {
////        console.debug("rectContains 2", r1.y, ">", r2.y)
//        return false;
//    }
//    if (r1.x + r1.width < r2.x + r2.width) {
////        console.debug("rectContains 3",
////                      r1.x + r1.width, "<", r2.x + r2.width,
////                      "r1", r1.x, r1.width,
////                      "r2", r2.x, r2.width)
//        return false;
//    }
//    if (r1.y + r1.height < r2.y + r2.height) {
////        console.debug("rectContains 4",
////                      r1.y + r1.height, "<", r2.y + r2.height,
////                      "r1", r1.y, r1.height,
////                      "r2", r2.y, r2.height)
//        return false;
//    }
//    return true

    return r1.x <= r2.x && r1.y <= r2.y
            && r1.x + r1.width >= r2.x + r2.width
            && r1.y + r1.height >= r2.y + r2.height
}

function rectFromMapVisibleRegion(visible_region) {
    const r = visible_region.boundingGeoRectangle()

    const p1_lon = r.bottomLeft.longitude
    var p2_lon = r.topRight.longitude
    if (p2_lon < p1_lon)
        p2_lon += 360

    return Qt.rect(p1_lon + 540,
                   r.bottomLeft.latitude,
                   p2_lon - p1_lon,
                   r.topRight.latitude - r.bottomLeft.latitude)
}

//function roundPoint(p) {
//    return Qt.point(p.x.toFixed(0), p.y.toFixed(0))
//}

//function isSamePixel(p1, p2) {
//    return Math.abs(p1.x - p2.x) < 1 && Math.abs(p1.y - p2.y) < 1
//}
