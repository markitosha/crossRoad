#include "model.h"

Model::Model() {
    roadNum = 1;
    roadWay = new LineRoadWay(Point(450, 123), Point(154, 235));
}

void Model::start() {
    Auto newAuto(3);
    newAuto.setPosition(((LineRoadWay*)roadWay)->getEntryPoint());
    roadWay->addAuto(newAuto);
}

void Model::step() {
    roadWay->autoArray[0].step(roadWay);
}
