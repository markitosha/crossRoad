#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "auto.h"
#include "road.h"
#include <iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    std::cout << "HELLO WORLD" << std::endl;
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,800,600, this);
    scene->setBackgroundBrush(Qt::green);
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());
//    generatorTimer = new QTimer(this);
   // connect(generatorTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));
//    generatorTimer->start(1000);
    // не просто добавить item дороги в сцену, но сначала посчитать в зависимости от количества дорог их расположение и координаты
    auto circle = new CircleRoad(400, 300, 100, 1, 1, 50);
    //scene -> addItem(new CircleRoadWay(0, 0, 100, 100, left));
    //scene -> addItem(circle);
    auto line = new LineRoad(350, 1, 1, 1, 600, 50);
    scene -> addItem(line);
    connect(line->roadways[0].generatorTimer, SIGNAL(timeout()), this, SLOT(line->roadways[0].generateAuto()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGenerate()
{
    //scene->addItem(new Auto());
}
