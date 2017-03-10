#include "mainwidget.h"
#include "auto.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget au;

    au.show();
    return a.exec();
}
