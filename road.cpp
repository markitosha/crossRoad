#include "road.h"

Road::Road(int l, int r, int w): width(w)
{
    roadways.clear();
    for (int i = 0; i < l; ++i) {
        RoadWay roadway(w, left);
        roadways.push_back(roadway);
    }
    for (int i = 0; i < r; ++i) {
        RoadWay roadway(w, right);
        roadways.push_back(roadway);
    }
}



Road::RoadWay::RoadWay(int w, int dir): width(w), direct(dir)
{
    autos.clear();
}

Road::RoadWay::RoadWay(const Road::RoadWay &obj)
{
    this->direct = obj.direct;
    this->width = obj.width;
    this->autos.clear();
    for (int i = 0; i < obj.autos.size(); ++i) {
        this->autos.push_back(obj.autos[i]);
    }
}
