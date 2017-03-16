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
