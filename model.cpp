#include "model.h"
#include <cmath>

Model::Model(int roadNum, int roadWayNum, int height, int width) : roadNum(roadNum), height(height), width(width) {
    stepCounter = 0;
    autoPerMinute = 100;
    auto center = Point(width / 2, height / 2);
    auto centerCircle = new CircleRoad(center, INNER_RADIUS * MST, roadWayNum);
    roads.push_back(centerCircle);
    float   angl2 = 5 * PI / 6,
            angl3 = 7 * PI / 6,
            rad = centerCircle->getFullRadius();

    roads.push_back(new LineRoad(Point(center.x, height), Point(center.x, center.y + rad), roadWayNum, center)); // 1 -  низ
    roads.push_back(new LineRoad(Point(center.x, 0), Point(center.x, center.y - rad), roadWayNum, center, OUT)); // 2 - верх
    roads.push_back(new LineRoad(Point(0, center.y * (1 + sin(angl2))), // 3 - лево низ
                                 Point(center.x + rad * cos(angl2), center.y + rad * sin(angl2)),
                                 roadWayNum, center));
    roads.push_back(new LineRoad(Point(0, center.y * (1 + sin(angl3))), // 4 -- лево верх
                                 Point(center.x + rad * cos(angl3), center.y + rad * sin(angl3)),
                                 roadWayNum, center));
    roads.push_back(new LineRoad(Point(width, center.y * (1 + sin(angl2))), // 5 -- право низ
                                 Point(center.x - rad * cos(angl2), center.y + rad * sin(angl2)),
                                 roadWayNum, center, OUT));
    roads.push_back(new LineRoad(Point(width, center.y * (1 + sin(angl3))), // 6 -- право верх
                                 Point(center.x - rad * cos(angl3), center.y + rad * sin(angl3)),
                                 roadWayNum, center, OUT));
}

void Model::generateAuto() {
    int startRoad = rand() % 5 + 1;
    int speed = rand() % 50 + 10;
    int finishRoad = rand() % 5 + 1;
    Auto * newAuto = new Auto(speed, startRoad, finishRoad);
    roads[startRoad] -> roadWays[1] -> addAuto(newAuto);
    newAuto->setModel(this);
}

void Model::start() {
    generateAuto();
}

void Model::step() {
    stepCounter++;

    if (stepCounter % (60000 / FPS / autoPerMinute) == 0) {
        generateAuto();
    }

    if (stepCounter == 60000 / FPS) {
        stepCounter = 0;
    }

    for(int i = 0; i < roads.size(); ++i) {
        Road *road = roads[i];
        for(int i = 0; i < road->roadWays.size(); ++i) {
            RoadWay *roadWay = road->roadWays[i];
            for(int i = 0; i < roadWay->autoArray.size(); ++i) {
                roadWay->autoArray[i]->step(roadWay);
            }
        }
    }
}
