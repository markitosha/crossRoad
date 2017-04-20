#ifndef AUTO_H
#define AUTO_H

#include "point.h"

enum Color {
    RED, GREEN, YELLOW
};

enum State {
    RUN, REBUILD
};

class Auto {
    Color color;
    State state;
    Point center;
    int speed;
    int startRoad;
    int finishRoad;
    int currentRoad;
    int nextRoad;
    int width;
    void * model;
    float angle;

public:
    Auto(int speed = 10, int startRoad = 0, int finishRoad = 0);

    void changeSpeed(int newSpeed);

    void setPosition(Point newPosition);

    void setModel(void *model);

    void step(void *currentRoadWay);

    Point getPosition();

    int getWidth();

    int getSpeed() {
        return speed;
    }
};

#endif // AUTO_H
