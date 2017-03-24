#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include <tuple>

#include "auto.h"

#include <iostream>

#include <QTimer>


enum {
    left, right
};


class RoadWay {
public:
    // ширина нужна для задания координат. Будем считать, что внутри одной дороги у нас только одинаковые полосы
    int direct;
    std::vector<Auto> autos;
    RoadWay(int dir = left);
    RoadWay(const RoadWay &obj);
};

class CircleRoadWay : public RoadWay, public QGraphicsEllipseItem {
    int posX;
    int posY;
    int inner;
   int width;
public:
    CircleRoadWay(int posX = 0, int posY = 0, int inner = 10, int w = 10, int dir = left): RoadWay(dir), QGraphicsEllipseItem(0),
    posX(posX), posY(posY), inner(inner), width(w)
    {
        QColor color(175, 175, 175);
        QColor color2(255, 255, 255);

        setBrush(color);
        setPen(color2);
        setRect(- width, - width,  2* width, 2 * width);
        //setPos(posX, posY);
    }
    CircleRoadWay(const CircleRoadWay &obj) {
        this->direct = obj.direct;
        this->autos.clear();
        this->posX = obj.posX;
        this->posY = obj.posY;
        this->inner = obj.inner;
        this->width = obj.width;
        for (int i = 0; i < obj.autos.size(); ++i) {
            this->autos.push_back(obj.autos[i]);
        }
        QColor color(175, 175, 175);
        QColor color2(255, 255, 255);

        setBrush(color);
        setPen(color2);
        setRect(- width, - width,  2* width, 2 * width);
        //setPos(posX, posY);
    }
};

class LineRoadWay : public RoadWay, public QGraphicsRectItem {
    int posX;
   int height;
   int width;

public:
   QTimer * generatorTimer;
   QTimer * animationTimer;

    LineRoadWay(int posX = 0, int h = 10, int w = 10, int dir = left): RoadWay(dir), QGraphicsRectItem(0),
    posX(posX), height(h), width(w) {
        QColor color(175, 175, 175);
        QColor color2(255, 255, 255);

        setBrush(color);
        setPen(color2);
        setRect(0, 0, width, height);
        setPos(posX, 0);
        generatorTimer = new QTimer();
        animationTimer = new QTimer();
    }
    LineRoadWay(const LineRoadWay &obj) {
        this->direct = obj.direct;
        this->autos.clear();
        this->posX = obj.posX;
        this->width = obj.width;
        this->height = obj.height;
        for (int i = 0; i < obj.autos.size(); ++i) {
            this->autos.push_back(obj.autos[i]);
        }
        QColor color(175, 175, 175);
        QColor color2(255, 255, 255);

        setBrush(color);
        setPen(color2);
        setRect(0, 0, width, height);
        setPos(posX, 0);
        generatorTimer = obj.generatorTimer;
        animationTimer = obj.animationTimer;
    }
    void generateAuto() {
        auto autom = new Auto();
        autom->setParentItem(this);
        //autos.push_back(autom);
    }
};

class Road: public QGraphicsRectItem
{
public:
    // во всем векторе надо задать координаты для путей. Можем повлиять извне на что-то кроме позиции? Реализовывается пусть внутри отнаследованных классов
    int width;
    // при создании делаем массив полос
    Road(int posX, int posY, int w): width(w)
    {
        QColor color(0, 255, 0);

        setPen(color);
        setRect(0, 0, 5 * w, 5 * w);
        setPos(posX, posY);
    }
};

class CircleRoad : public Road {
    int centerX;
    int centerY;
    int innerCircle;
    std::vector<CircleRoadWay> roadways;
    QGraphicsEllipseItem * innerItem;
public:
    CircleRoad(int posX = 0, int posY = 0, int inner = 10, int l = 1, int r = 1, int w = 10) : Road(posX, posY, w),
        centerX(posX), centerY(posY), innerCircle(inner) {
        roadways.clear();
        for (int i = 0, size = (l + r) * width + innerCircle / 2; i < l; ++i, size -= 2 * width) {
            CircleRoadWay roadway(centerX, centerY, innerCircle, size, left);
            roadways.push_back(roadway);
        }
        for (int i = 0, size = r * width + innerCircle / 2 ; i < r; ++i, size -= 2 * width) {
            CircleRoadWay roadway(centerX, centerY, innerCircle, size, right);
            roadways.push_back(roadway);
        }
        for (int i = 0; i < roadways.size(); ++i) {
            roadways[i].setParentItem(this);
        }
        innerItem = new QGraphicsEllipseItem(this);
        innerItem->setBrush(Qt::green);
        innerItem->setPen(QColor(255, 255, 255));
        innerItem->setRect(- innerCircle / 2, - innerCircle / 2, innerCircle, innerCircle);
    }
};

class LineRoad: public Road
{
public:
    std::vector<LineRoadWay> roadways;

    // надо проинициализировать все полосы, привести к нужному классу, задать координаты и собственно нарисовать
    LineRoad(int posX = 0, int posY = 0, int l = 1, int r = 1, int h = 50, int w = 10) : Road(posX, posY, w)
    {
        roadways.clear();
        int pos = 0;
        for (int i = 0; i < l; ++i) {
            LineRoadWay roadway(pos, h, w, left);
            roadways.push_back(roadway);
            pos += width;
        }
        for (int i = 0 ; i < r; ++i) {
            LineRoadWay roadway(pos, h, w, right);
            roadways.push_back(roadway);
            pos += width;
        }
        for (int i = 0; i < roadways.size(); ++i) {
            roadways[i].setParentItem(this);
        }
    }
};

#endif // ROAD_H
