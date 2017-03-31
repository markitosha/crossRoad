#include "model.h"

//Model::Model() {
//    roadNum = 1;
// //    roadWay = new LineRoadWay(Point(450, 123), Point(154, 235));
// //    roadWay2 = new CircleRoadWay(Point(250, 250), 200.0);
// //    road = new LineRoad(Point(450, 123), Point(154, 235), 2);
//    road = new CircleRoad(Point(250, 250), 50, 3);

//}

Model::Model(int roadNum, int roadWayNum, int height, int width) : roadNum(roadNum), height(height), width(width) {
    auto center = Point(width / 2, height / 2);
    auto centerCircle = new CircleRoad(center, INNER_RADIUS * MST, roadWayNum);
    roads.push_back(centerCircle);

    roads.push_back(new LineRoad(Point(center.x, height), Point(center.x, center.y + centerCircle->getFullRadius()), roadWayNum, center));

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
