#ifndef AUTO_H
#define AUTO_H

#include "point.h"

enum Color {
    RED, GREEN, YELLOW, BLACK
};

enum StateAuto {
    RUN, REBUILD
};

class Auto {
    Color color;
    StateAuto state;
    Point center;
    int speed;
    int startRoad;
    int finishRoad;
    int currentRoad;
    int nextRoad;
    int width;
    int minSpeed;
    int maxSpeed;
    void * model;
    float angle;
    float k;

    void * checkRoadWay(void* roadWay);
    void checkSpeed(void *roadWay);
    void changeSpeed(int newSpeed);

public:
    Auto(int speed = 10, int startRoad = 0, int finishRoad = 0);

    void setPosition(Point newPosition);

    void setModel(void *model);

    void step(void *currentRoadWay);

    Point getPosition();

    int getWidth();

    int getSpeed() {
        return speed;
    }

    Color getColor() {
        return color;
    }
};

#endif // AUTO_H
