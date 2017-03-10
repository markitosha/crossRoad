#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QTimer>

namespace Ui {
    class Widget;
}

class Road: public QGraphicsRectItem {

};

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

    // QGraphicsItem interface
public:
    void advance(int phase);
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onGenerate();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QTimer *animationTimer;
    QTimer *generatorTimer;

};

#endif // WIDGET_H
