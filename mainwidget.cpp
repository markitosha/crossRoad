#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "auto.h"
#include <iostream>

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
    animationTimer->start(1000);

    myModel = new Model();
    myModel->start();

    Point entryPoint = ((LineRoadWay*)(myModel->roadWay))->getEntryPoint();
    Point endPoint = ((LineRoadWay*)(myModel->roadWay))->getEndPoint();
    scene->addLine(entryPoint.x, entryPoint.y,
                   endPoint.x, endPoint.y);
    Point center = ((LineRoadWay*)(myModel->roadWay))->autoArray[0].getPosition();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-5, -5, 10, 10);
    circle->setPos(center.x, center.y);
    scene->addItem(circle);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGenerate()
{
    scene->clear();
    myModel->step();
    Point entryPoint = ((LineRoadWay*)(myModel->roadWay))->getEntryPoint();
    Point endPoint = ((LineRoadWay*)(myModel->roadWay))->getEndPoint();
    scene->addLine(entryPoint.x, entryPoint.y, endPoint.x, endPoint.y);
    Point center = ((LineRoadWay*)(myModel->roadWay))->autoArray[0].getPosition();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-5, -5, 10, 10);
    circle->setPos(center.x, center.y);
    scene->addItem(circle);
}
