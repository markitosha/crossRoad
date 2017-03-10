#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,800,600, this);
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());
    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    animationTimer->start(1000/60);
    generatorTimer = new QTimer(this);
    connect(generatorTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));
    generatorTimer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGenerate()
{
    scene->addItem(new Auto());
}

Auto::Auto(int cX, int cY, int r, int sp, int bR, int eR): QGraphicsEllipseItem(0),
    centerX(cX), centerY(cY), radius(r), speed(sp), beginRoad(bR), endRoad(eR) {
    color = QColor(0, 0, 0);
    setBrush(color);
    setRect(0, 0, radius, radius);
    setPos(centerX, centerY);
}

void Auto::advance(int phase) {
    if (phase) {
        moveBy(0, speed);
    }
}
