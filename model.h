#ifndef MODEL_H
#define MODEL_H

#include "road.h"
#include "constants.h"

class Model
{
    int roadNum;
    int height;
    int width;

public:
    vector <Road *> roads;

    Model(int roadNum, int roadWayNum, int height, int width);

    void start();

    void step();
};

#endif // MODEL_H
