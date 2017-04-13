#include "road.h"

Road::Road(int roadWayNum) : roadWayNum(roadWayNum) {
    width = WIDTH_ROADWAY * MST;
}

LineRoad::LineRoad(Point entryPoint,  Point endPoint, int roadWayNum, Point center) : Road(roadWayNum), entryPoint(entryPoint), endPoint(endPoint) {
    Line centralLine(entryPoint, endPoint);
    Line perpendicular = centralLine.perpendicular(entryPoint);
    Circle mainCircle(center.distance(endPoint), center.x, center.y);

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

CircleRoad::CircleRoad(Point centerPoint, int innerCircleR, int roadWayNum) : Road(roadWayNum), centerPoint(centerPoint), innerCircleRadius(innerCircleR) {
    for (int i = 0, offset = innerCircleRadius + width / 2; i < roadWayNum; ++i, offset += width) {
        CircleRoadWay * newRoadWay;

        newRoadWay = new CircleRoadWay(centerPoint, offset);

        roadWays.push_back(newRoadWay);
    }
}
