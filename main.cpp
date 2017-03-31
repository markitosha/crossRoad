#include "interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface au;

    au.show();
    return a.exec();
}
