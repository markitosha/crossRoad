#include "interface.h"
#include "ui_mainwidget.h"
#include "constants.h"
#include <iostream>

void renderAuto(Auto *aut, QGraphicsScene *scene) {
    Point center = aut->getPosition();
    int width = aut->getWidth() * MST;
    QColor color;
    switch (aut->getColor()) {
    case RED:
        color = Qt::red;
        break;
    case GREEN:
        color = Qt::darkMagenta;
        break;
    case YELLOW:
        color = Qt::yellow;
        break;
    case BLACK:
        color = Qt::darkRed;
        break;
    default:
        color = Qt::green;
    }

    if (aut->getSpeed() < 0) {
        color = Qt::black;
    }

    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-width / 2, -width / 2, width, width);
    QString speed = QString::number(aut->getSpeed());
    QGraphicsTextItem *text = new QGraphicsTextItem(speed);
    text->setPos(center.x - width / 2, center.y - width / 2);
    circle->setPos(center.x, center.y);
    circle->setBrush(color);
    scene->addItem(circle);
    scene->addItem(text);
}

void renderLineRoadWay(LineRoadWay *roadWay, QGraphicsScene *scene) {
    Point entryPoint = roadWay->getEntryPoint();
    Point endPoint = roadWay->getEndPoint();
    scene->addLine(entryPoint.x, entryPoint.y, endPoint.x, endPoint.y);

    for (int i = 0; i < roadWay->autoArray.size(); ++i) {
        renderAuto(roadWay->autoArray[i], scene);
    }
}

void renderCircleRoadWay(CircleRoadWay *roadWay, QGraphicsScene *scene) {
    int radius = roadWay->getRadius();
    Point center = roadWay->getCenterPoint();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-radius, -radius, 2 * radius, 2 * radius);
    circle->setPos(center.x, center.y);
    scene->addItem(circle);

    for (int i = 0; i < roadWay->autoArray.size(); ++i) {
        renderAuto(roadWay->autoArray[i], scene);
    }
}

void renderLineRoad(LineRoad * road, QGraphicsScene *scene ) {
    for (int i = 0; i < road->roadWays.size(); ++i) {
        renderLineRoadWay((LineRoadWay *)road->roadWays[i], scene);
    }

    Point entryPoint = road->getEntryPoint();
    Point endPoint = road->getEndPoint();
    scene->addLine(entryPoint.x, entryPoint.y, endPoint.x, endPoint.y, road->isOpen() ? QPen(Qt::white) : QPen(Qt::red));
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

Interface::Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,500,500, this);
    scene->setBackgroundBrush(Qt::green);
    ui->graphicsView->setScene(scene);

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));
    animationTimer->start(1000 / FPS);

    myModel = new Model(1, 2, 500, 500);
    myModel->start();

    renderModel(myModel, scene);
    stepCounter = 0;
}

Interface::~Interface()
{
    delete ui;
}

void Interface::onGenerate()
{
    scene->clear();
    myModel->step();

    renderModel(myModel, scene);
}
