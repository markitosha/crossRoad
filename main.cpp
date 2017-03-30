#include "mainwidget.h"
#include "model.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget au;
    Model model;
    model.start();

    au.show();
    return a.exec();
}
