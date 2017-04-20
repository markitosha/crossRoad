#ifndef MODEL_H
#define MODEL_H

#include "road.h"
#include "constants.h"
#include <random>

class Model
{
    int roadNum;
    int height;
    int width;
    int stepCounter;
    int autoPerMinute;

public:
    vector <Road *> roads;

    Model(int roadNum, int roadWayNum, int height, int width);

    void start();

    void step();

    CircleRoad * getCircleRoad() {
        return (CircleRoad*)roads[0];
    }

    RoadWay * getMyRoadWay(Auto * aut) {
        for(int i = 0; i < roads.size(); ++i) {
            Road *road = roads[i];
            for(int i = 0; i < road->roadWays.size(); ++i) {
                RoadWay *roadWay = road->roadWays[i];
                for(int i = 0; i < roadWay->autoArray.size(); ++i) {
                    if (roadWay->autoArray[i] == aut) {
                        return roadWay;
                    }
                }
            }
        }
    }

    void generateAuto();
};

#endif // MODEL_H
