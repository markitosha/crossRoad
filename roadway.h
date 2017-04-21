#ifndef ROADWAY_H
#define ROADWAY_H

#include <vector>
#include <cmath>

#include "auto.h"
#include "constants.h"

using namespace std;

enum Direct {
    LEFT, RIGHT
};

class RoadWay
{
public:
    vector<Auto *> autoArray; // массив машин
    // конструктор
    RoadWay() {
        autoArray.clear();
    }
    // добавить машину на полосу
    virtual void addAuto(Auto *newAuto) = 0;
    // вычислить новую позицию
    virtual Point calcOffssetPosition(Point oldPosition, int speed, float angle) = 0;
    // получить машину спереди
    virtual Auto * getAheadAuto(Auto *aut) = 0;
    // свободна ли перед машиной полоса
    virtual bool isEmpty(Auto * aut) = 0;
    // удалить машину с полосы
    void deleteAuto(Auto *oldAuto);
};

class LineRoadWay: public RoadWay {
    Point entryPoint; // входная точка
    Point endPoint; // выходная точка
    float lineCos; // косинус угла наклона прямой
    float lineSin; // синус угла наклона прямой

public:
    // конструктор
    LineRoadWay(Point entryPoint, Point endPoint);
    // посчитать смещение
    Point calcOffssetPosition(Point oldPosition, int speed, float angle);
    // добавить машину
    void addAuto(Auto *newAuto);
    // получить входную точку
    Point getEntryPoint() {
        return entryPoint;
    }
    // получить выходную точку
    Point getEndPoint() {
        return endPoint;
    }
    // получить машину спереди
    Auto * getAheadAuto(Auto *aut);
    // свободна ли полоса впереди для данной машины
    bool isEmpty(Auto * aut);
};

class CircleRoadWay: public RoadWay {
    Point centerPoint; // центр круговой дороги
    float radius; // радиус траектории полосы

public:
    // конструктор
    CircleRoadWay(Point centerPoint, float radius);
    // посчитать смещение
    Point calcOffssetPosition(Point oldPosition, int speed, float angle);
    // добавить машину
    void addAuto(Auto *newAuto) {
        autoArray.push_back(newAuto);
    }
    // получить центр
    Point getCenterPoint() {
        return centerPoint;
    }
    // поучить радиус
    int getRadius() {
        return radius;
    }
    // получить машину, приближающуюся к нам по соседней полосе
    Auto * getAheadAuto(Auto *aut);
    // получить машину позади нас
    Auto * getPrevAuto(Auto *aut);
    // свободна ли дорога перед машиной
    bool isEmpty(Auto * aut);
};

#endif // ROADWAY_H
