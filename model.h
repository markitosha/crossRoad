#ifndef MODEL_H
#define MODEL_H

#include "roadway.h"

class Model
{
public:
    int roadNum;
    RoadWay *roadWay;

    Model();

    void start();

    void step();
};

#endif // MODEL_H
