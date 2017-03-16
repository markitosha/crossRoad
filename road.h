#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include "auto.h"

using namespace std;

enum {
    left, right
};

class Road
{
    class RoadWay {
        int width,
            direct;
        vector<Auto> autos;

    public:
        RoadWay(int w = 10, int dir = left);
        RoadWay(const RoadWay &obj);
    };

    vector<RoadWay> roadways;
    int width;

public:
    Road(int l = 1, int r = 1, int w = 10);
};

#endif // ROAD_H
