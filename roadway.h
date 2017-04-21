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
    virtual Auto * getAheadAuto(Auto *aut) = 0;
    virtual bool isEmpty(Auto * aut) = 0;

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

    Auto * getAheadAuto(Auto *aut) {
        if (autoArray.size() <= 1) {
            return NULL;
        }

        int distance = 10000000;
        Point position = aut->getPosition();
        float endDist = position.distance(endPoint);
        Auto * currAuto = NULL;

        for (int i = 0; i < autoArray.size(); ++i) {
            if (aut != autoArray[i]) {
                Point currPosition = autoArray[i]->getPosition();
                float currDist = position.distance(currPosition);
                float currEndDist = currPosition.distance(endPoint);
                if (currDist < distance && currEndDist < endDist && currDist < 3 * MST * aut->getWidth()) {
                    currAuto = autoArray[i];
                }
            }
        }

        return currAuto;
    }

    bool isEmpty(Auto * aut) {
        Auto * lastAuto = autoArray.size() > 0 ? autoArray.back() : NULL;

        if (!lastAuto) {
            return true;
        }

        float distance = lastAuto->getPosition().distance(entryPoint);
        float width = lastAuto->getWidth() * MST * 3;

        return distance >= width;
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

    Auto * getAheadAuto(Auto *aut);

    Auto * getPrevAuto(Auto *aut);

    bool isEmpty(Auto * aut) {
        Auto * aheadAuto = getAheadAuto(aut);
        Auto * prevAuto = getPrevAuto(aut);

        return !aheadAuto && !prevAuto;
    }
};

#endif // ROADWAY_H
