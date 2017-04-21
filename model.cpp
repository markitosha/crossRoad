#include "model.h"
#include <cmath>

void Model::init(int roadNm, int min, int max, int autoPerMin) {
    int roadWayNum = 2;
    stepCounter = 0;
    autoPerMinute = autoPerMin;
    minSpeed = min;
    maxSpeed = max;
    roadNum = roadNm;
    height = HEIGHT_SCREEN;
    width = WIDTH_SCREEN;
    auto center = Point(width / 2, height / 2);
    auto centerCircle = new CircleRoad(center, INNER_RADIUS * MST, roadWayNum);
    roads.push_back(centerCircle);
    float   angl2 = 5 * PI / 6,
            angl3 = 7 * PI / 6,
            rad = centerCircle->getFullRadius();
    roads.push_back(new LineRoad(Point(center.x, height), Point(center.x, center.y + rad), roadWayNum, center, IN, roadNum-- > 0)); // 1 -  низ
    roads.push_back(new LineRoad(Point(center.x, 0), Point(center.x, center.y - rad), roadWayNum, center, OUT, roadNum-- > 0)); // 2 - верх
    roads.push_back(new LineRoad(Point(0, center.y * (1 + sin(angl2))), // 3 - лево низ
                                 Point(center.x + rad * cos(angl2), center.y + rad * sin(angl2)),
                                 roadWayNum, center, IN, roadNum-- > 0));
    roads.push_back(new LineRoad(Point(0, center.y * (1 + sin(angl3))), // 4 -- лево верх
                                 Point(center.x + rad * cos(angl3), center.y + rad * sin(angl3)),
                                 roadWayNum, center, IN, roadNum-- > 0));
    roads.push_back(new LineRoad(Point(width, center.y * (1 + sin(angl2))), // 5 -- право низ
                                 Point(center.x - rad * cos(angl2), center.y + rad * sin(angl2)),
                                 roadWayNum, center, OUT, roadNum-- > 0));
    roads.push_back(new LineRoad(Point(width, center.y * (1 + sin(angl3))), // 6 -- право верх
                                 Point(center.x - rad * cos(angl3), center.y + rad * sin(angl3)),
                                 roadWayNum, center, OUT, roadNum-- > 0));
    state = START;
}

void Model::generateAuto() {
    int startRoad = 0;
    int finishRoad = 0;
    int count = 0;

    do {
        startRoad = rand() % 6 + 1;
        if (++count > 10000) {
            return;
        }
    } while (!roads[startRoad]->roadWays[1]->isEmpty(NULL) || !roads[startRoad]->isOpen());

    count = 0;
    do {
        finishRoad = rand() % 6 + 1;
        if (++count > 10000) {
            return;
        }
    } while (!roads[finishRoad]->isOpen());

    int speed = rand() % (maxSpeed - minSpeed) + minSpeed;
    Auto * newAuto = new Auto(speed, startRoad, finishRoad);
    roads[startRoad] -> roadWays[1] -> addAuto(newAuto);
    newAuto->setModel(this);
}

void Model::start(int roadNm, int min, int max, int autoPerMin) {
    if (state == START) {
        state = PAUSE;
    } else if (state == STOP) {
        init(roadNm, min, max, autoPerMin);
        generateAuto();
    } else {
        state = START;
        generateAuto();
    }
}

void Model::stop() {
    for(int i = 0; i < roads.size(); ++i) {
        Road *road = roads[i];
        for(int i = 0; i < road->roadWays.size(); ++i) {
            RoadWay *roadWay = road->roadWays[i];
            roadWay->autoArray.clear();
        }
        road->roadWays.clear();
    }

    roads.clear();

    state = STOP;
}

void Model::step() {
    if (state == START) {
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
}

RoadWay * Model::getMyRoadWay(Auto * aut) {
    for(int i = 0; i < roads.size(); ++i) {
        Road *road = roads[i];
        for(int i = 0; i < road->roadWays.size(); ++i) {
            RoadWay *roadWay = road->roadWays[i];
            for(int i = 0; i < roadWay->autoArray.size(); ++i) {
                if (roadWay->autoArray[i] == aut) {
                    return roadWay;
                }
            }
        }
    }
}
