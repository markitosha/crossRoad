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

void Auto::moveBy(Point offset) {
    center.x += offset.x * speed;
    center.y += offset.y * speed;
}

void Auto::changeSpeed(int newSpeed) {
    color = newSpeed > speed ? RED : (newSpeed < speed ? YELLOW : GREEN);
    speed = newSpeed;
}

void Auto::setPosition(Point newPosition) {
    center = newPosition;
}

void Auto::step(void *currentRoudWay) {
    this->moveBy(((LineRoadWay*)currentRoudWay)->calcOffssetPosition(speed));
    cout << center.x << " " << center.y << endl;
}
