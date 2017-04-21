#include "road.h"

Road::Road(int roadWayNum, bool open) : roadWayNum(roadWayNum), open(open) {
    width = WIDTH_ROADWAY * MST;
}

LineRoad::LineRoad(Point entryPoint,  Point endPoint, int roadWayNum, Point center, Dir pos, bool open) : Road(roadWayNum, open), entryPoint(entryPoint), endPoint(endPoint) {
    Line centralLine(entryPoint, endPoint);
    Line perpendicular = centralLine.perpendicular(entryPoint);
    Circle mainCircle(center.distance(endPoint), center.x, center.y);
    float linesin = perpendicular.a != 0 ? sin(atan(perpendicular.a)) : 1;
    float linecos = perpendicular.a != 0 ? cos(atan(perpendicular.a)) : 1;
    float firstOffset = pos == IN ? - width / 2 - width * (roadWayNum / 2 - 1) : width / 2 + width * (roadWayNum / 2 - 1);
    float off = pos == IN ? width : - width;

    for (int i = 0, offset = firstOffset; i < roadWayNum; ++i, offset += off) {
        LineRoadWay * newRoadWay;

        Point endOffset(endPoint.x + linesin * offset, endPoint.y + linecos * offset);
        Point entryOffset(entryPoint.x + linesin * offset, entryPoint.y + linecos * offset);

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
    open = true;

    for (int i = 0, offset = innerCircleRadius + width / 2; i < roadWayNum; ++i, offset += width) {
        CircleRoadWay * newRoadWay;

        newRoadWay = new CircleRoadWay(centerPoint, offset);

        roadWays.push_back(newRoadWay);
    }
}
