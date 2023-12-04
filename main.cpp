#include"qapplication.h"
#include"pets.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	petsWidget w;	//窗口对象
	w.show();	//生成窗口
	return a.exec();
}