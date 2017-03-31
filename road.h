#ifndef ROAD_H
#define ROAD_H

#include <vector>

#include "roadway.h"
#include "line.h"
#include "circle.h"
#include "constants.h"

class Road
{
protected:
    int width;
    int roadWayNum;

public:
    vector<RoadWay *> roadWays;
    Road(int roadWayNum);
};

class LineRoad : public Road {
    Point entryPoint;
    Point endPoint;

public:
    LineRoad(Point entryPoint,  Point endPoint, int roadWayNum, Point center);

    Point getEntryPoint() {
        return entryPoint;
    }

    Point getEndPoint() {
        return endPoint;
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
        return innerCircleRadius + width * roadWays.size() - width / 2;
    }
};

#endif // ROAD_H
