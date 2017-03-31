#include "roadway.h"

LineRoadWay::LineRoadWay(Point entryPoint, Point endPoint) : entryPoint(entryPoint), endPoint(endPoint) {
    double arctan = atan2(endPoint.y - entryPoint.y, endPoint.x - entryPoint.x);
    lineCos = cos(arctan);
    lineSin = sin(arctan);
}

Point LineRoadWay::calcOffssetPosition(Point oldPosition, int speed) {
    if (speed == 0) {
        return oldPosition;
    }

    return Point(oldPosition.x + lineCos * speed, oldPosition.y + lineSin * speed);
}

void LineRoadWay::addAuto(Auto &newAuto) {
    newAuto.setPosition(entryPoint);
    autoArray.push_back(newAuto);
}

CircleRoadWay::CircleRoadWay(Point centerPoint, float radius)
    : radius(radius) {
    this->centerPoint.x = centerPoint.x;
    this->centerPoint.y = centerPoint.y;
    time = 0;
}

Point CircleRoadWay::calcOffssetPosition(Point oldPosition, int speed) {
    if (speed == 0) {
        return oldPosition;
    }

    time += 1; // полный круг -- радиус
    return Point(centerPoint.x + radius * cos(speed / radius * PI * time), centerPoint.y + radius * sin(speed / radius * PI * time));
}
