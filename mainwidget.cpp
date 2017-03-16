#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "auto.h"
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
