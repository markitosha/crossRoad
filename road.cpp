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

RoadWay * LineRoad::canGetIn(Auto *aut) {
    LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
    float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
    float width = aut->getWidth();

    if (distance <= width) {
        return newRoadWay;
    }

    return NULL;
}

bool LineRoad::soonRebase(Auto *aut) {
    LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
    float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
    float maxWidth = aut->getWidth() * MST * 1.5;
    float minWidth = aut->getWidth() * MST * 0.5;
    return distance <= maxWidth && distance >= minWidth;
}

bool LineRoad::waitingEmpty(Auto *aut) {
    LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
    float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
    float maxWidth = aut->getWidth() * MST * 0.5;
    float minWidth = aut->getWidth() * MST * 0.4;
    return distance <= maxWidth && distance >= minWidth;
}

bool LineRoad::rebaseStarted(Auto *aut) {
    LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
    float distance = newRoadWay->getEntryPoint().distance(aut->getPosition());
    float minWidth = aut->getWidth() * MST * 0.4;
    return distance < minWidth;
}

RoadWay * CircleRoad::canGetIn(Auto *aut) {
    float distance = centerPoint.distance(aut->getPosition());

    if (distance <= aut->getWidth() + getFullRadius()) {
        return this->roadWays[1];
    }

    return NULL;
}

bool CircleRoad::soonRebase(Auto *aut) {
    float distance = centerPoint.distance(aut->getPosition());
    float maxWidth = aut->getWidth() * MST * 2 + getFullRadius();
    float minWidth = aut->getWidth() * MST + getFullRadius();
    return distance <= maxWidth && distance >= minWidth;
}

bool CircleRoad::waitingEmpty(Auto *aut) {
    float distance = centerPoint.distance(aut->getPosition());
    float maxWidth = aut->getWidth() * MST * 1.5 + getFullRadius();
    float minWidth = aut->getWidth() * MST + getFullRadius();
    return distance <= maxWidth && distance >= minWidth;
}

bool CircleRoad::rebaseStarted(Auto *aut) {
    float distance = centerPoint.distance(aut->getPosition());
    float minWidth = aut->getWidth() * MST + getFullRadius();
    return distance < minWidth;
}
