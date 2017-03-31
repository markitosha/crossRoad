#include <iostream>
#include "auto.h"
#include "constants.h"
#include "roadway.h"

using namespace std;

Auto::Auto(int speed, int startRoad, int finishRoad) :
    speed(speed), startRoad(startRoad), finishRoad(finishRoad)
{
    state = RUN;
    color = GREEN;
    currentRoad = startRoad;
    width = WIDTH_AUTO;
    center = Point();
}

void Auto::changeSpeed(int newSpeed) {
    color = newSpeed > speed ? RED : (newSpeed < speed ? YELLOW : GREEN);
    speed = newSpeed;
}

void Auto::setPosition(Point newPosition) {
    center.x = newPosition.x;
    center.y = newPosition.y;
}

void Auto::step(void *currentRoudWay) {
    setPosition(((RoadWay*)currentRoudWay)->calcOffssetPosition(center, speed));
}

Point Auto::getPosition() {
    return center;
}

int Auto::getWidth() {
    return width;
}
