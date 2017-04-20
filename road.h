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
};

class LineRoad : public Road {
    Point entryPoint;
    Point endPoint;

public:
    LineRoad(Point entryPoint,  Point endPoint, int roadWayNum, Point center, Dir pos = IN);

    Point getEntryPoint() {
        return entryPoint;
    }

    Point getEndPoint() {
        return endPoint;
    }

    RoadWay * canGetIn(Auto *aut) {
        LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
        if (newRoadWay->getEntryPoint().distance(aut->getPosition()) <= aut->getWidth()) {
            return newRoadWay;
        }

        return NULL;
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
        if (centerPoint.distance(aut->getPosition()) <= getFullRadius()) {
            return this->roadWays[1];
        }

        return NULL;
    }
};

#endif // ROAD_H
