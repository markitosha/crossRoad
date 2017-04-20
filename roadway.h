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
    vector<Auto *> autoArray;

    RoadWay() {
        autoArray.clear();
    }

    virtual void addAuto(Auto *newAuto) = 0;
    virtual Point calcOffssetPosition(Point oldPosition, int speed, float angle) = 0;

    void deleteAuto(Auto *oldAuto) {
        int pos;

        for (int i = 0; i < autoArray.size(); ++i) {
            if (autoArray[i] == oldAuto) {
                pos = i;
                break;
            }
        }
        autoArray.erase(autoArray.begin() + pos);
    }
};

class LineRoadWay: public RoadWay {
    Point entryPoint;
    Point endPoint;
    float lineCos;
    float lineSin;

public:
    LineRoadWay(Point entryPoint, Point endPoint);

    Point calcOffssetPosition(Point oldPosition, int speed, float angle);

    void addAuto(Auto *newAuto);

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
    int time;

public:
    CircleRoadWay(Point centerPoint, float radius);

    Point calcOffssetPosition(Point oldPosition, int speed, float angle);

    void addAuto(Auto *newAuto) {
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
