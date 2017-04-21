#include "interface.h"
#include "ui_mainwidget.h"
#include "constants.h"
#include <iostream>

void Interface::renderAuto(Auto *aut) {
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
    circle->setPen(color);
    circle->setZValue(1000);
    text->setZValue(1001);
    scene->addItem(circle);
    scene->addItem(text);
}

void Interface::renderLineRoadWay(LineRoadWay *roadWay, bool open) {
    Point entryPoint = roadWay->getEntryPoint();
    Point endPoint = roadWay->getEndPoint();
    QPen pen(QColor(open ? Qt::gray : Qt::darkRed), WIDTH_ROADWAY * MST);
    scene->addLine(entryPoint.x, entryPoint.y, endPoint.x, endPoint.y, pen);

    for (int i = 0; i < roadWay->autoArray.size(); ++i) {
        renderAuto(roadWay->autoArray[i]);
    }
}

void Interface::renderCircleRoadWay(CircleRoadWay *roadWay) {
    int radius = roadWay->getRadius() + MST * WIDTH_ROADWAY / 2;
    Point center = roadWay->getCenterPoint();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-radius, -radius, 2 * radius, 2 * radius);
    circle->setPos(center.x, center.y);
    circle->setBrush(Qt::gray);
    circle->setPen(QColor(Qt::white));
    circle->setZValue(900);
    scene->addItem(circle);

    for (int i = 0; i < roadWay->autoArray.size(); ++i) {
        renderAuto(roadWay->autoArray[i]);
    }
}

void Interface::renderLineRoad(LineRoad * road) {
    for (int i = 0; i < road->roadWays.size(); ++i) {
        renderLineRoadWay((LineRoadWay *)road->roadWays[i], road->isOpen());
    }

    Point entryPoint = road->getEntryPoint();
    Point endPoint = road->getEndPoint();
    scene->addLine(entryPoint.x, entryPoint.y, endPoint.x, endPoint.y, road->isOpen() ? QPen(Qt::white) : QPen(Qt::red));
}

void Interface::renderCircleRoad(CircleRoad * road) {
    for (int i = road->roadWays.size() - 1; i >= 0; --i) {
        renderCircleRoadWay((CircleRoadWay *)road->roadWays[i]);
    }

    int innerRadius = road->getInnerRadius() + MST * WIDTH_ROADWAY;
    Point center = road->getCenterPoint();
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-innerRadius, -innerRadius, 2 * innerRadius, 2 * innerRadius);
    circle->setPos(center.x, center.y);
    circle->setBrush(Qt::green);
    circle->setPen(QColor(Qt::white));
    circle->setZValue(950);
    scene->addItem(circle);
}

void Interface::renderModel(Model * model) {
    renderCircleRoad((CircleRoad *)model->roads[0]);

    for (int i = 1; i < model->roads.size(); ++i) {
        renderLineRoad((LineRoad *)model->roads[i]);
    }
 }






Interface::Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,HEIGHT_SCREEN,WIDTH_SCREEN, this);
    scene->setBackgroundBrush(Qt::green);
    ui->graphicsView->setScene(scene);

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));

    myModel = new Model();
}

Interface::~Interface()
{
    delete ui;
}

void Interface::onGenerate()
{
    scene->clear();
    myModel->step();

    renderModel(myModel);
}

void Interface::on_pushButton_clicked()
{
    animationTimer->start(1000 / FPS);
    int max = ui->lineEdit->text().toInt();
    int min = ui->lineEdit_2->text().toInt();
    int autosPerMin = ui->lineEdit_3->text().toInt();
    int roadNum = ui->lineEdit_4->text().toInt();
    myModel->start(roadNum, min, max, autosPerMin);
    renderModel(myModel);

    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);

    if (ui->pushButton->text() == "Старт") {
        ui->pushButton->setText("Пауза");
    } else {
        ui->pushButton->setText("Старт");
    }

    ui->pushButton_2->setDisabled(false);
}

void Interface::on_pushButton_2_clicked()
{
    myModel->stop();
    scene->clear();
    animationTimer->stop();
    ui->pushButton->setText("Старт");
    ui->pushButton_2->setDisabled(true);
    ui->lineEdit->setDisabled(false);
    ui->lineEdit_2->setDisabled(false);
    ui->lineEdit_3->setDisabled(false);
    ui->lineEdit_4->setDisabled(false);

}
