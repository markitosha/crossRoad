#include <iostream>
#include "auto.h"
#include "constants.h"
#include "roadway.h"
#include "model.h"

using namespace std;

Auto::Auto(int speed, int startRoad,int finishRoad) :
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

void Auto::setModel(void * model) {
    this->model = model;
    Model * myModel = (Model*)this->model;
    CircleRoad * circle = myModel->getCircleRoad();
    float centerY = circle->getCenterPoint().y;
    float radius = circle->getFullRadius();
    LineRoadWay * myRoadWay = (LineRoadWay*)myModel->getMyRoadWay(this);
    Point endY = myRoadWay->getEndPoint();
    float k = 0;
    switch (startRoad) {
    case 1:
        k = 50.0;
        break;
    case 2:
        k = 15.0;
        break;
    case 3:
        k = 125.0;
        break;
    case 4:
        k = 125.0;
        break;
    case 5:
        k = 125.0;
        break;
    case 6:
        k = 187.0;
        break;
    default:
        k = 50.0;
        break;
    }
    angle = k / ((float)speed) * radius * asin((centerY - endY.y) / radius);
}

void Auto::step(void *currentRoudWay) {
    Road * currentRoadPointer = ((Model*)model)->roads[currentRoad];
    Road * startRoadPointer = ((Model*)model)->roads[startRoad];
    Road * finishRoadPointer = ((Model*)model)->roads[finishRoad];
    RoadWay * roadWay = (RoadWay*)currentRoudWay;
    int nextRoad = 0;

    if (currentRoadPointer != finishRoadPointer) {
        if (currentRoadPointer == startRoadPointer) {
            nextRoad = 0;
        } else {
            nextRoad = finishRoad;
        }

        Road * nextRoadPointer = ((Model*)model)->roads[nextRoad];

        RoadWay * getIn = nextRoadPointer->canGetIn(this);

         if (getIn) {
             currentRoad = nextRoad;
             currentRoudWay = getIn;
             roadWay->deleteAuto(this);
             roadWay = getIn;
             roadWay->addAuto(this);
         }
    }

    setPosition(((RoadWay*)currentRoudWay)->calcOffssetPosition(center, speed, angle++));
}

Point Auto::getPosition() {
    return center;
}

int Auto::getWidth() {
    return width;
}
