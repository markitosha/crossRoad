#ifndef ROADWAY_H
#define ROADWAY_H

#include <vector>
#include <cmath>

#include "auto.h"
#include "constants.h"

using namespace std;

enum Direct {
    LEFT, RIGHT
};

class RoadWay
{
public:
    vector<Auto> autoArray;

    RoadWay() {
        autoArray.clear();
    }

    virtual void addAuto(Auto &newAuto) = 0;

   // virtual bool canAddAuto() = 0;
   // virtual Auto& findNearestAuto(Point point) = 0;
   // virtual int findMaxSpeed(Point point) = 0;
    virtual Point calcOffssetPosition(Point oldPosition, int speed) = 0;
};

class LineRoadWay: public RoadWay {
    Point entryPoint;
    Point endPoint;
    float lineCos;
    float lineSin;

public:
    LineRoadWay(Point entryPoint, Point endPoint) : entryPoint(entryPoint), endPoint(endPoint) {
        double arctan = atan2(endPoint.y - entryPoint.y, endPoint.x - entryPoint.x);
        lineCos = cos(arctan);
        lineSin = sin(arctan);
    }

    Point calcOffssetPosition(Point oldPosition, int speed) {
        if (speed == 0) {
            return oldPosition;
        }

        return Point(oldPosition.x + lineCos * speed, oldPosition.y + lineSin * speed);
    }

    void addAuto(Auto &newAuto) {
        newAuto.setPosition(entryPoint);
        autoArray.push_back(newAuto);
    }

    Point getEntryPoint() {
        return entryPoint;
    }

    Point getEndPoint() {
        return endPoint;
    }
};

class CircleRoadWay: public RoadWay {
    Point centerPoint;
    float radius;
    float period;

public:
    CircleRoadWay(Point centerPoint, float radius)
        : radius(radius) {
        this->centerPoint.x = centerPoint.x;
        this->centerPoint.y = centerPoint.y;
        period = - PI;
    }

    Point calcOffssetPosition(Point oldPosition, int speed) {
        if (speed == 0) {
            return oldPosition;
        }

        period += PI / 2;
        return Point(centerPoint.x + radius * cos(speed / radius * period), centerPoint.y + radius * sin(speed / radius * period));
    }

    void addAuto(Auto &newAuto) {
        autoArray.push_back(newAuto);
    }

    Point getCenterPoint() {
        return centerPoint;
    }

    int getRadius() {
        return radius;
    }
};

#endif // ROADWAY_H
