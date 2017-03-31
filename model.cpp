#include "model.h"

Model::Model() {
    roadNum = 1;
    roadWay = new LineRoadWay(Point(450, 123), Point(154, 235));
    roadWay2 = new CircleRoadWay(Point(250, 250), 100.0);
}

void Model::start() {
    Auto newAuto(3);
    Auto newAuto2(1);
    newAuto.setPosition(((LineRoadWay*)roadWay)->getEntryPoint());
    newAuto2.setPosition(Point(250, 150));
    roadWay->addAuto(newAuto);
    roadWay2->addAuto(newAuto2);
}

void Model::step() {
    roadWay->autoArray[0].step(roadWay);
    roadWay2->autoArray[0].step(roadWay2);
}
