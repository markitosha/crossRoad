#ifndef ROAD_H
#define ROAD_H

#include <vector>

#include "roadway.h"
#include "line.h"
#include "circle.h"
#include "constants.h"

enum Dir {
    IN, OUT
};

class Road
{
protected:
    int width;
    int roadWayNum;
    bool open;

public:
    vector<RoadWay *> roadWays;
    Road(int roadWayNum, bool open = true);
    virtual RoadWay * canGetIn(Auto *aut) = 0;
    virtual bool soonRebase(Auto *aut) = 0;
    virtual bool waitingEmpty(Auto *aut) = 0;
    virtual bool rebaseStarted(Auto *aut) = 0;
    virtual bool isEmpty(Auto *aut) = 0;

    bool isOpen() {
        return open;
    }
};

class LineRoad : public Road {
    Point entryPoint;
    Point endPoint;

public:
    LineRoad(Point entryPoint,  Point endPoint, int roadWayNum, Point center, Dir pos = IN, bool open = true);

    Point getEntryPoint() {
        return entryPoint;
    }

    Point getEndPoint() {
        return endPoint;
    }

    RoadWay * canGetIn(Auto *aut) {
        LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
        float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
        float width = aut->getWidth();

        if (distance <= width) {
            return newRoadWay;
        }

        return NULL;
    }

    bool isEmpty(Auto *aut) {
        LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
        return newRoadWay->isEmpty(aut);
    }

    bool soonRebase(Auto *aut) {
        LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
        float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
        float maxWidth = aut->getWidth() * MST * 1.5;
        float minWidth = aut->getWidth() * MST * 0.5;
        return distance <= maxWidth && distance >= minWidth;
    }

    bool waitingEmpty(Auto *aut) {
        LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
        float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
        float maxWidth = aut->getWidth() * MST * 0.5;
        float minWidth = aut->getWidth() * MST * 0.4;
        return distance <= maxWidth && distance >= minWidth;
    }

    bool rebaseStarted(Auto *aut) {
        LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
        float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
        float minWidth = aut->getWidth() * MST * 0.4;
        return distance < minWidth;
    }
};

class CircleRoad : public Road {
    Point centerPoint;
    int innerCircleRadius;

public:
    CircleRoad(Point centerPoint, int innerCircleR, int roadWayNum);

    int getInnerRadius() {
        return innerCircleRadius;
    }

    Point getCenterPoint() {
        return centerPoint;
    }

    float getFullRadius() {
        return ((CircleRoadWay*)roadWays[1])->getRadius();
    }

    RoadWay * canGetIn(Auto *aut) {
        float distance = centerPoint.distance(aut->getPosition());

        if (distance <= aut->getWidth() + getFullRadius()) {
            return this->roadWays[1];
        }

        return NULL;
    }

    bool isEmpty(Auto *aut) {
        return this->roadWays[1]->isEmpty(aut);
    }

    bool soonRebase(Auto *aut) {
        float distance = centerPoint.distance(aut->getPosition());
        float maxWidth = aut->getWidth() * MST * 2 + getFullRadius();
        float minWidth = aut->getWidth() * MST + getFullRadius();
        return distance <= maxWidth && distance >= minWidth;
    }

    bool waitingEmpty(Auto *aut) {
        float distance = centerPoint.distance(aut->getPosition());
        float maxWidth = aut->getWidth() * MST * 1.5 + getFullRadius();
        float minWidth = aut->getWidth() * MST + getFullRadius();
        return distance <= maxWidth && distance >= minWidth;
    }

    bool rebaseStarted(Auto *aut) {
        float distance = centerPoint.distance(aut->getPosition());
        float minWidth = aut->getWidth() * MST + getFullRadius();
        return distance < minWidth;
    }
};

#endif // ROAD_H
