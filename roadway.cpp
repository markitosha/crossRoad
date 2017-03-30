#include "roadway.h"

//RoadWay::RoadWay() {
//    autoArray.clear();
//}

//LineRoadWay::LineRoadWay(Point entryPoint, Point endPoint) : entryPoint(entryPoint), endPoint(endPoint) {
//    double arctan = atan2(endPoint.y - entryPoint.y, endPoint.x - entryPoint.x);
//    lineCos = cos(arctan);
//    lineSin = sin(arctan);
//}

//Point LineRoadWay::calcOffssetPosition(int speed) {
//    if (speed == 0) {
//        return Point(0, 0);
//    }

//    return Point(lineCos * speed, lineSin * speed);
//}

//void LineRoadWay::addAuto(Auto &newAuto) {
//    newAuto.setPosition(entryPoint);
//    autoArray.push_back(newAuto);
//}
