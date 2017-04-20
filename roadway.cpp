#include "roadway.h"

LineRoadWay::LineRoadWay(Point entryPoint, Point endPoint) : entryPoint(entryPoint), endPoint(endPoint) {
    double arctan = atan2(endPoint.y - entryPoint.y, endPoint.x - entryPoint.x);
    lineCos = cos(arctan);
    lineSin = sin(arctan);
}

Point LineRoadWay::calcOffssetPosition(Point oldPosition, int speed, float angle) {
    if (speed == 0) {
        return oldPosition;
    }

    return Point(oldPosition.x + lineCos * speed / FPS, oldPosition.y + lineSin * speed / FPS);
}

void LineRoadWay::addAuto(Auto *newAuto) {
    newAuto->setPosition(entryPoint);
    autoArray.push_back(newAuto);
}

CircleRoadWay::CircleRoadWay(Point centerPoint, float radius)
    : radius(radius) {
    this->centerPoint.x = centerPoint.x;
    this->centerPoint.y = centerPoint.y;
    time = 182;
}

Point CircleRoadWay::calcOffssetPosition(Point oldPosition, int speed, float angle) {
    if (speed == 0) {
        return oldPosition;
    }

    return Point(centerPoint.x + radius * cos(speed / radius * angle / FPS), centerPoint.y - radius * sin(speed / radius * angle / FPS));
}
