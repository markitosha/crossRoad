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
    int width;

public:
    Auto(int speed = 10, int startRoad = 0, int finishRoad = 0);

    void moveBy(Point offset);

    void changeSpeed(int newSpeed);

    void setPosition(Point newPosition);

    void step(void *currentRoudWay);

    Point getPosition() {
        return center;
    }
};

#endif // AUTO_H
