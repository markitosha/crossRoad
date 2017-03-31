#ifndef ROAD_H
#define ROAD_H

#include <vector>

#include "roadway.h"
#include "constants.h"

class Road
{
protected:
    int width;
    int roadWayNum;

public:
    vector<RoadWay *> roadWays;
    Road(int roadWayNum) : roadWayNum(roadWayNum) {
        width = WIDTH_ROADWAY * MST;
    }
};

class LineRoad : public Road {
    Point entryPoint;
    Point endPoint;

public:
    LineRoad(Point entryPoint,  Point endPoint, int roadWayNum) : Road(roadWayNum), entryPoint(entryPoint), endPoint(endPoint) {
        for (int i = 0, offset =  - width / 2 - width * (roadWayNum / 2 - 1); i < roadWayNum; ++i, offset += width) {
            LineRoadWay * newRoadWay;
            Point endOffset(endPoint.x + offset, endPoint.y + offset);
            Point entryOffset(entryPoint.x + offset, entryPoint.y + offset);

            if (i < roadWayNum / 2) {
                newRoadWay = new LineRoadWay(endOffset, entryOffset);
            } else {
                newRoadWay = new LineRoadWay(entryOffset, endOffset);
            }

            roadWays.push_back(newRoadWay);
        }
    }

    Point getEntryPoint() {
        return entryPoint;
    }

    Point getEndPoint() {
        return endPoint;
    }
};

#endif // ROAD_H
