#ifndef ROAD_H
#define ROAD_H

#include <vector>

#include "roadway.h"
#include "line.h"
#include "circle.h"
#include "constants.h"

enum Dir {
    IN, OUT
};

class Road
{
protected:
    int width; // ширина
    int roadWayNum; // номер
    bool open; // открыта ли

public:
    vector<RoadWay *> roadWays; // массив полос
    // конструктор
    Road(int roadWayNum, bool open = true);
    // можно ли войти
    virtual RoadWay * canGetIn(Auto *aut) = 0;
    // ????
    virtual bool soonRebase(Auto *aut) = 0;
    // ???
    virtual bool waitingEmpty(Auto *aut) = 0;
    // ??
    virtual bool rebaseStarted(Auto *aut) = 0;
    // пустая ли
    virtual bool isEmpty(Auto *aut) = 0;
    // открыта ли
    bool isOpen() {
        return open;
    }
};

class LineRoad : public Road {
    Point entryPoint; // начало середней полосы дороги
    Point endPoint; // конец средней полосы дороги

public:
    // конструктор
    LineRoad(Point entryPoint,  Point endPoint, int roadWayNum, Point center, Dir pos = IN, bool open = true);
    // получить входную точку
    Point getEntryPoint() {
        return entryPoint;
    }
    // получить выходную точку
    Point getEndPoint() {
        return endPoint;
    }
    // на какую полосу можно заехать
    RoadWay * canGetIn(Auto *aut);
    // пустая ли
    bool isEmpty(Auto *aut) {
        LineRoadWay * newRoadWay = (LineRoadWay*)this->roadWays[0];
        return newRoadWay->isEmpty(aut);
    }

    bool soonRebase(Auto *aut);

    bool waitingEmpty(Auto *aut);

    bool rebaseStarted(Auto *aut);
};

class CircleRoad : public Road {
    Point centerPoint; // центр круговой дороги
    int innerCircleRadius; // радиус внутренней окружности

public:
    // конструктор
    CircleRoad(Point centerPoint, int innerCircleR, int roadWayNum);
    // получить радиус внутреннего круга
    int getInnerRadius() {
        return innerCircleRadius;
    }
    // получит координаты центра
    Point getCenterPoint() {
        return centerPoint;
    }
    // получить полный радиус
    float getFullRadius() {
        return ((CircleRoadWay*)roadWays[1])->getRadius();
    }
    // можно ли войти на полосу
    RoadWay * canGetIn(Auto *aut);
    // пустая ли
    bool isEmpty(Auto *aut) {
        return this->roadWays[1]->isEmpty(aut);
    }

    bool soonRebase(Auto *aut);

    bool waitingEmpty(Auto *aut);

    bool rebaseStarted(Auto *aut);
};

#endif // ROAD_H
