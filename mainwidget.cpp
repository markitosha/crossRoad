#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "constants.h"
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

void renderAuto(Auto &aut, QGraphicsScene *scene) {
    Point center = aut.getPosition();
    int width = aut.getWidth() * MST;
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-width / 2, -width / 2, width, width);
    circle->setPos(center.x, center.y);
    scene->addItem(circle);
}

void renderLineRoad(LineRoad * road, QGraphicsScene *scene ) {
    for (int i = 0; i < road->roadWays.size(); ++i) {
        renderLineRoadWay((LineRoadWay *)road->roadWays[i], scene);
    }

    Point entryPoint = road->getEntryPoint();
    Point endPoint = road->getEndPoint();
    scene->addLine(entryPoint.x, entryPoint.y, endPoint.x, endPoint.y, QPen(Qt::white));
}

void renderCircleRoad(CircleRoad * road, QGraphicsScene *scene) {
    for (int i = 0; i < road->roadWays.size(); ++i) {
        renderCircleRoadWay((CircleRoadWay *)road->roadWays[i], scene);
    }

    int innerRadius = road->getInnerRadius();
    Point center = road->getCenterPoint();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-innerRadius, -innerRadius, 2 * innerRadius, 2 * innerRadius);
    circle->setPos(center.x, center.y);
    circle->setPen(QColor(255, 255, 255));
    scene->addItem(circle);
}

void renderModel(Model * model, QGraphicsScene *scene) {
    renderCircleRoad((CircleRoad *)model->roads[0], scene);

    for (int i = 1; i < model->roads.size(); ++i) {
        renderLineRoad((LineRoad *)model->roads[i], scene);
    }
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

    myModel = new Model(1, 2, 500, 500);
    myModel->start();

    renderModel(myModel, scene);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGenerate()
{
    scene->clear();
    myModel->step();

    renderModel(myModel, scene);
}
