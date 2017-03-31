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
    Road(int roadWayNum) : roadWayNum(roadWayNum) {
        width = WIDTH_ROADWAY * MST;
    }
};

class LineRoad : public Road {
    Point entryPoint;
    Point endPoint;

public:
    LineRoad(Point entryPoint,  Point endPoint, int roadWayNum, Point center) : Road(roadWayNum), entryPoint(entryPoint), endPoint(endPoint) {
        Line centralLine(entryPoint, endPoint);
        Line perpendicular = centralLine.perpendicular(entryPoint);
        Circle mainCircle(center.x, center.y, center.distance(endPoint));

        for (int i = 0, offset =  - width / 2 - width * (roadWayNum / 2 - 1); i < roadWayNum; ++i, offset += width) {
            LineRoadWay * newRoadWay;

            Point endOffset(endPoint.x + offset, endPoint.y + offset);
            Point entryOffset(entryPoint.x + offset, entryPoint.y + offset);

            Line offsetLine(entryOffset, endOffset);
            Point entryOffsetPoint = offsetLine.crossLine(perpendicular);
            Point endOffsetPoint = mainCircle.crossLine(offsetLine, endOffset);

            if (i < roadWayNum / 2) {
                newRoadWay = new LineRoadWay(endOffsetPoint, entryOffsetPoint);
            } else {
                newRoadWay = new LineRoadWay(entryOffsetPoint, endOffsetPoint);
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

class CircleRoad : public Road {
    Point centerPoint;
    int innerCircleRadius;

public:
    CircleRoad(Point centerPoint, int innerCircleR, int roadWayNum) : Road(roadWayNum), centerPoint(centerPoint), innerCircleRadius(innerCircleR) {
        for (int i = 0, offset = innerCircleRadius + width / 2; i < roadWayNum; ++i, offset += width) {
            CircleRoadWay * newRoadWay;

            newRoadWay = new CircleRoadWay(centerPoint, offset);

            roadWays.push_back(newRoadWay);
        }
    }

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
