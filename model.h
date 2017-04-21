#ifndef MODEL_H
#define MODEL_H

#include "road.h"
#include "constants.h"
#include <random>

enum State {
    START, PAUSE, STOP
};

class Model
{
    int roadNum; // количество открытых дорог
    int height; // высота модели
    int width; // ширина модели
    int autoPerMinute; // частота генерации машин
    int stepCounter; // счетчик шагов

    // инициализация модели
    void init(int roadNm, int min, int max, int autoPerMin);

public:
    int maxSpeed; // максимально возможная скорость машины
    int minSpeed; // минимально возможная скорость машины
    State state; // состояние модели (пауза, стоп, старт)

    vector <Road *> roads; // массив дорог

    // конструктор по умолчанию
    Model() {
        state = STOP;
    }

    // начало работы
    void start(int roadNm, int min, int max, int autoPerMin);
    // шаг
    void step();
    // остановка
    void stop();
    // получить круговую дорогу
    CircleRoad * getCircleRoad() {
        return (CircleRoad*)roads[0];
    }
    // получить полосу, на которой сейчас автомобиль
    RoadWay * getMyRoadWay(Auto * aut);
    // сгенерировать машину
    void generateAuto();
};

#endif // MODEL_H
