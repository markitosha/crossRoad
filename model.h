#ifndef MODEL_H
#define MODEL_H

#include "road.h"
#include "constants.h"
#include <random>

enum State {
    START, PAUSE, STOP
};

class Model
{
    int roadNum;
    int height;
    int width;
    int autoPerMinute;
    int stepCounter;

    void init(int roadNm, int min, int max, int autoPerMin);

public:
    int maxSpeed;
    int minSpeed;
    State state;

    vector <Road *> roads;

    Model() {
        state = STOP;
    }

    void start(int roadNm, int min, int max, int autoPerMin);

    void step();

    void stop();

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
