#ifndef MODEL_H
#define MODEL_H

#include "road.h"

class Model
{
public:
    int roadNum;
    Road *road;

    Model();

    void start();

    void step();
};

#endif // MODEL_H
