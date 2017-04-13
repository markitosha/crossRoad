#include "model.h"
#include <cmath>

Model::Model(int roadNum, int roadWayNum, int height, int width) : roadNum(roadNum), height(height), width(width) {
    auto center = Point(width / 2, height / 2);
    auto centerCircle = new CircleRoad(center, INNER_RADIUS * MST, roadWayNum);
    roads.push_back(centerCircle);
    float   angl2 = 5 * PI / 6,
            angl3 = 7 * PI / 6,
            rad = centerCircle->getFullRadius();

    roads.push_back(new LineRoad(Point(center.x, height), Point(center.x, center.y + rad), roadWayNum, center));
    roads.push_back(new LineRoad(Point(center.x, 0), Point(center.x, center.y - rad), roadWayNum, center));
    roads.push_back(new LineRoad(Point(0, center.y * (1 + sin(angl2))),
                                 Point(center.x + rad * cos(angl2), center.y + rad * sin(angl2)),
                                 roadWayNum, center));
    roads.push_back(new LineRoad(Point(0, center.y * (1 + sin(angl3))),
                                 Point(center.x + rad * cos(angl3), center.y + rad * sin(angl3)),
                                 roadWayNum, center));
    roads.push_back(new LineRoad(Point(width, center.y * (1 + sin(angl2))),
                                 Point(center.x - rad * cos(angl2), center.y + rad * sin(angl2)),
                                 roadWayNum, center));
    roads.push_back(new LineRoad(Point(width, center.y * (1 + sin(angl3))),
                                 Point(center.x - rad * cos(angl3), center.y + rad * sin(angl3)),
                                 roadWayNum, center));

    for (int i = 0; i < roadNum; ++i) {
       // roads.push_back(new LineRoad(Point(width / 2))
    }
}

void Model::start() {
     Auto newAuto(3);
     Point center = ((CircleRoad *)roads[0]) -> getCenterPoint();
     newAuto.setPosition(Point(center.x,  center.y - ((CircleRoad *)roads[0]) -> getFullRadius()));
     roads[0] -> roadWays[1] -> addAuto(newAuto);
}

void Model::step() {
 //    roadWay->autoArray[0].step(roadWay);
     roads[0] -> roadWays[1] -> autoArray[0].step(roads[0] -> roadWays[1]);
}
