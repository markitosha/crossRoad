#ifndef MODEL_H
#define MODEL_H

#include "road.h"
#include "constants.h"

class Model
{
    int roadNum;
    int height;
    int width;

public:
    vector <Road *> roads;

    Model(int roadNum, int roadWayNum, int height, int width) : roadNum(roadNum), height(height), width(width) {
        auto center = Point(width / 2, height / 2);
        auto centerCircle = new CircleRoad(center, INNER_RADIUS * MST, roadWayNum);
        roads.push_back(centerCircle);

        roads.push_back(new LineRoad(Point(center.x, height), Point(center.x, center.y + centerCircle->getFullRadius()), roadWayNum));

        for (int i = 0; i < roadNum; ++i) {
           // roads.push_back(new LineRoad(Point(width / 2))
        }
    }

    void start() {};

    void step() {};
};

#endif // MODEL_H
