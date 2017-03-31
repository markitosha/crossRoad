#ifndef MODEL_H
#define MODEL_H

#include "roadway.h"

class Model
{
public:
    int roadNum;
    RoadWay *roadWay;
    RoadWay *roadWay2;

    Model();

    void start();

    void step();
};

#endif // MODEL_H
