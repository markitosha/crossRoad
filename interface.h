#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QTimer>

#include "model.h"

namespace Ui {
    class Widget;
}

class Interface : public QWidget
{
    Q_OBJECT
    void renderModel(Model * model);
    void renderCircleRoad(CircleRoad * road);
    void renderLineRoad(LineRoad * road);
    void renderCircleRoadWay(CircleRoadWay *roadWay);
    void renderLineRoadWay(LineRoadWay *roadWay, bool open = true);
    void renderAuto(Auto *aut);
public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();

private slots:
    void onGenerate();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QTimer *animationTimer;
    QTimer *generatorTimer;
    Model *myModel;

};

#endif // WIDGET_H
