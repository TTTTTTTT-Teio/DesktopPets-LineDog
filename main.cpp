#include "widget.h"
#include "normalmode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    normalmode w;
    w.show();
    return a.exec();
}
