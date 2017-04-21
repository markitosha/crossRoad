#ifndef AUTO_H
#define AUTO_H

#include "point.h"

enum Color {
    RED, GREEN, YELLOW, BLACK
};

enum StateAuto {
    RUN, REBUILD
};

class Auto {
    Color color; // цвет
    StateAuto state; // состояние: едет по своей полосе/перестраивается   ???
    Point center; // координаты центра
    int speed; // скорость
    int startRoad; // номер дороги, с которой начинается движение
    int finishRoad; // номер дороги, на которой заканчивается движение
    int currentRoad; // номер текущей дороги
    int nextRoad; // номер следующей дороги
    int width; // ширина машины
    int minSpeed; // минимальная скорость
    int maxSpeed; // максимальная скорость
    void * model; // указатель на модель
    float angle; // угол                        ???
    float k; //                                 ???
    int waitingTime;

    void * checkRoadWay(void* roadWay); // можно ли перестроиться, и если да, то куда ??
    void checkSpeed(void *roadWay); // узнать текущую скорость
    void changeSpeed(int newSpeed); // изменить скорость

public:
    // конструктор
    Auto(int speed = 10, int startRoad = 0, int finishRoad = 0);
    // задать позицию
    void setPosition(Point newPosition);
    // задать модель
    void setModel(void *model);
    // один шаг
    void step(void *currentRoadWay);
    // получить позицию
    Point getPosition();
    // получить ширину
    int getWidth();
    // получить скорость
    int getSpeed() {
        return speed;
    }
    // получить цвет
    Color getColor() {
        return color;
    }
};

#endif // AUTO_H
