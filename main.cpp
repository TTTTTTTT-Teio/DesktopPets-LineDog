#include "widget.h"
#include "normalmode.h"
#include "movemode.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    //这是一个cpp结课报告
    QApplication a(argc, argv);
    normalmode* w = new normalmode();
    w->show();
    return a.exec();
}
