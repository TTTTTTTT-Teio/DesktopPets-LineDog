#include "widget.h"
#include "QGraphicsDropShadowEffect"

widget::widget(QWidget *parent)
    : QWidget(parent)
{

}

void widget::WidgetsParameter()
{
	setWindowFlags(Qt::WindowType::FramelessWindowHint);	//无边框
	setAttribute(Qt::WA_TranslucentBackground);	//背景透明
	setWindowIcon(QIcon(":/Icon/dogs/windowsicon/icom.png"));
}

void widget::ShadowEffect()
{
	//窗口设置阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(230, 230, 230, 220));
	effect->setBlurRadius(1);
	this->setGraphicsEffect(effect);
}

widget::~widget()
{

}
