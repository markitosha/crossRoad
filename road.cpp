#include "road.h"

RoadWay::RoadWay(int dir): direct(dir)
{
    autos.clear();
}

RoadWay::RoadWay(const RoadWay &obj)
{
    this->direct = obj.direct;
    this->autos.clear();
    for (int i = 0; i < obj.autos.size(); ++i) {
        this->autos.push_back(obj.autos[i]);
    }
}
