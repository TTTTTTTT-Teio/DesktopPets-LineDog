#include "normalmode.h"
#include "movemode.h"
#include "washmode.h"
#include "qtimer.h"
#include "QMovie"
#include "QMouseEvent"

washmode::washmode(QWidget* parent)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	setAttribute(Qt::WA_DeleteOnClose);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	washmode::updateRoleAnimation();
}

void washmode::updateRoleAnimation()
{
	WashModeRoleAnimation();
	updateAnimationTimer();
	returnNormalModeTimer();
}

void washmode::updateAnimationTimer()
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->setInterval(100);
	connect(updateTimer, &QTimer::timeout, this, &washmode::WashModeRoleAnimation);
	updateTimer->start();
}

void washmode::WashModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	roleLabel->resize(200, 200);	//设置窗口大小
	roleLabel->setStyleSheet(qcut + QString("background-image:url(:/wash/dogs/wash/%1.png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = curFrame + 1;	//循环展示背景图片
}

void washmode::returnNormalModeTimer()
{
	QTimer* returnTimer = new QTimer(this);
	returnTimer->setTimerType(Qt::PreciseTimer);
	returnTimer->setSingleShot(true);
	returnTimer->setInterval(3000);
	connect(returnTimer, &QTimer::timeout, this, &washmode::returnNormalMode);
	returnTimer->start();
}

void washmode::returnNormalMode()
{
	static int clickAreaX, clickAreaY;
	normalmode* n = new normalmode();
	clickAreaX = this->x();
	clickAreaY = this->y();
	n->move(clickAreaX - 35, clickAreaY + 75);
	n->show();
	this->close();
}

washmode::~washmode()
{

}