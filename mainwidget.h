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
    Model *myModel;
};

#endif // WIDGET_H
