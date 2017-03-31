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

class Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();

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
