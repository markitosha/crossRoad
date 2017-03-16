#ifndef AUTO_H
#define AUTO_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QTimer>

class Auto: public QGraphicsEllipseItem {
    QColor color;
    int centerX,
        centerY,
        radius,
        speed,
        beginRoad,
        endRoad;

public:
    Auto(int cX = 0, int cY = 0, int r = 100, int sp = 10, int bR = 1, int eR = 4);
    Auto(const Auto &obj);

    // QGraphicsItem interface
public:
    void advance(int phase);
};

#endif // AUTO_H
