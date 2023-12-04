#include "desktoppets_linedogs.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DesktopPets_LineDogs w;	//窗口对象
	w.show();	//生成窗口
	return a.exec();
}
