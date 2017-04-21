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
    nextRoad = 0;
}

void Auto::changeSpeed(int newSpeed) {
    newSpeed = newSpeed > maxSpeed ? maxSpeed : newSpeed;
    newSpeed = newSpeed < 0 ? 0 : newSpeed;
    color = newSpeed > speed ? RED : (newSpeed < speed ? YELLOW : GREEN);
    angle = newSpeed == 0 ? (speed == 0 ? angle : angle * (float)speed) : (speed == 0 ? angle / (float)newSpeed : angle * (float)speed / (float)newSpeed);
    speed = newSpeed;
}

void Auto::setPosition(Point newPosition) {
    center.x = newPosition.x;
    center.y = newPosition.y;
}

void Auto::setModel(void * model) {
    this->model = model;
    Model * myModel = (Model*)this->model;
    minSpeed = myModel->minSpeed;
    maxSpeed = myModel->maxSpeed;
    CircleRoad * circle = myModel->getCircleRoad();
    float centerY = circle->getCenterPoint().y;
    float radius = circle->getFullRadius();
    LineRoadWay * myRoadWay = (LineRoadWay*)myModel->getMyRoadWay(this);
    Point endY = myRoadWay->getEndPoint();
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

void * Auto::checkRoadWay(void *roadWay) {
    if (nextRoad != -1) {
        Road * nextRoadPointer = ((Model*)model)->roads[nextRoad];

        if (nextRoadPointer->isEmpty(this) || nextRoadPointer->rebaseStarted(this)) {
            RoadWay * getIn = nextRoadPointer->canGetIn(this);

            if (getIn) {
                currentRoad = nextRoad;
                nextRoad = nextRoad == 0 ? finishRoad : -1;
                ((RoadWay*)roadWay)->deleteAuto(this);
                roadWay = getIn;
                ((RoadWay*)roadWay)->addAuto(this);
            }
        } else {
            if (nextRoadPointer->waitingEmpty(this)) {
                changeSpeed(0);
            }
        }
    }

    return roadWay;
}

void Auto::checkSpeed(void *roadWay) {
    bool soonRebase = false;
    if (nextRoad != -1) {
        Road * nextRoadPointer = ((Model*)model)->roads[nextRoad];
        soonRebase = nextRoadPointer->soonRebase(this);
    }
    Auto * aheadAuto = ((RoadWay*)roadWay)->getAheadAuto(this);

    if (aheadAuto) {
        int aheadSpeed = aheadAuto->getSpeed();
        float distance = center.distance(aheadAuto->getPosition());
        bool bigDist = distance > 2.5 * width * MST;

        if (!soonRebase && aheadSpeed > speed && bigDist) {
            changeSpeed(speed + 1);
        } else if (bigDist && (soonRebase || aheadSpeed < speed)) {
            changeSpeed(speed - 1);
        } else if (!bigDist) {
            changeSpeed(aheadSpeed);
        } else {
            changeSpeed(speed);
        }
    } else {
        if (speed == 0) {
            changeSpeed(maxSpeed * 3 / 5);
        }

        if (soonRebase) {
            changeSpeed(speed - 1 > minSpeed ? speed - 1 : minSpeed);
        } else {
            changeSpeed(speed + 1);
        }
    }
}

void Auto::step(void *currentRoadWay) {
    RoadWay * roadWay = (RoadWay*)currentRoadWay;

    checkSpeed(roadWay);
    roadWay = (RoadWay*)checkRoadWay(roadWay);

    if (nextRoad == -1 && ((LineRoadWay*)roadWay)->getEndPoint().distance(center) < width) {
        roadWay->deleteAuto(this);
    } else {
        setPosition(roadWay->calcOffssetPosition(center, speed, angle++));
    }
}

Point Auto::getPosition() {
    return center;
}

int Auto::getWidth() {
    return width;
}
