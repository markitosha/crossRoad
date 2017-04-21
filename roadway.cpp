#include "roadway.h"
#include "line.h"

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

Auto * CircleRoadWay::getAheadAuto(Auto *aut) {
    if (autoArray.size() <= 1) {
        return NULL;
    }

    int distance = 10000000;
    Point position = aut->getPosition();
    Line line(position, centerPoint);
    bool positiveSign = line.a >= 0; // true, если возрастает, false, если убывает. Для крайних случаев true
    Auto * currAuto = NULL;

    for (int i = 0; i < autoArray.size(); ++i) {
        if (aut != autoArray[i]) {
            Point currPosition = autoArray[i]->getPosition();
            float currDist = position.distance(currPosition);
            if (currDist < distance && (positiveSign || line.apply(currPosition) > 0) && currDist < 3 * MST * aut->getWidth()) {
                currAuto = autoArray[i];
            }
        }
    }

    return currAuto;
}

Auto * CircleRoadWay::getPrevAuto(Auto *aut) {
    if (autoArray.size() == 0) {
        return NULL;
    }

    int distance = 10000000;
    Point position = aut->getPosition();
    Line line(position, centerPoint);
    bool positiveSign = line.a >= 0; // true, если возрастает, false, если убывает. Для крайних случаев true
    Auto * currAuto = NULL;

    for (int i = 0; i < autoArray.size(); ++i) {
        if (aut != autoArray[i]) {
            Point currPosition = autoArray[i]->getPosition();
            float currDist = position.distance(currPosition);
            if (currDist < distance && (!positiveSign || line.apply(currPosition) < 0)  && currDist < 3 * MST * aut->getWidth()) {
                currAuto = autoArray[i];
            }
        }
    }

    return currAuto;
}
