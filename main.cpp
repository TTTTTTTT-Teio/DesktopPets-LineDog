#include "widget.h"
#include "normalmode.h"
#include "movemode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    normalmode* w = new normalmode();
    w->show();
    return a.exec();
}
