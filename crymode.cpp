#include "normalmode.h"
#include "crymode.h"

crymode::crymode(QWidget* parent)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	setAttribute(Qt::WA_DeleteOnClose);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	crymode::updateRoleAnimation();
}

void crymode::updateRoleAnimation()
{
	CryModeRoleAnimation();
	updateAnimationTimer();
	returnNormalModeTimer();
}

void crymode::updateAnimationTimer()
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->setInterval(100);
	connect(updateTimer, &QTimer::timeout, this, &crymode::CryModeRoleAnimation);
	updateTimer->start();
}

void crymode::CryModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	QString qpos("background-position: bottom left;");
	roleLabel->resize(200, 200);	//设置窗口大小
	roleLabel->setStyleSheet(qpos + qcut + QString("background-image:url(:/cry/dogs/cry/%1.png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = curFrame + 1;	//循环展示背景图片
}

void crymode::returnNormalModeTimer()
{
	QTimer* returnTimer = new QTimer(this);
	returnTimer->setTimerType(Qt::PreciseTimer);
	returnTimer->setSingleShot(true);
	returnTimer->setInterval(3000);
	connect(returnTimer, &QTimer::timeout, this, &crymode::returnNormalMode);
	returnTimer->start();
}

void crymode::returnNormalMode()
{
	static int clickAreaX, clickAreaY;
	normalmode* n = new normalmode();
	clickAreaX = this->x();
	clickAreaY = this->y();
	n->move(clickAreaX - 40, clickAreaY + 100);
	n->show();
	this->close();
}

crymode::~crymode()
{

}