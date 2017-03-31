#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "auto.h"
#include <iostream>

void renderLineRoadWay(LineRoadWay *roadWay, QGraphicsScene *scene) {
    Point entryPoint = roadWay->getEntryPoint();
    Point endPoint = roadWay->getEndPoint();
    scene->addLine(entryPoint.x, entryPoint.y, endPoint.x, endPoint.y);
}

void renderCircleRoadWay(CircleRoadWay *roadWay, QGraphicsScene *scene) {
    int radius = roadWay->getRadius();
    Point center = roadWay->getCenterPoint();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-radius, -radius, 2 * radius, 2 * radius);
    circle->setPos(center.x, center.y);
    scene->addItem(circle);
}

void renderAuto(Auto &aut, QGraphicsScene *scene ) {
    Point center = aut.getPosition();
    int width = aut.getWidth();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-width / 2, -width / 2, width, width);
    circle->setPos(center.x, center.y);
    scene->addItem(circle);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,500,500, this);
    scene->setBackgroundBrush(Qt::green);
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));
    animationTimer->start(100);

    myModel = new Model();
    myModel->start();

    renderCircleRoadWay((CircleRoadWay *)myModel->roadWay2, scene);
    renderAuto(myModel->roadWay2->autoArray[0], scene);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGenerate()
{
    scene->clear();
    myModel->step();

    renderCircleRoadWay((CircleRoadWay *)myModel->roadWay2, scene);
    renderAuto(myModel->roadWay2->autoArray[0], scene);
}
