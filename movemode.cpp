#include "normalmode.h"
#include "movemode.h"
#include "qtimer.h"
#include "QMovie"
#include "QMouseEvent"

movemode::movemode(QWidget* parent)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	setAttribute(Qt::WA_DeleteOnClose);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	movemode::updateRoleAnimation();
	this->installEventFilter(this);
}

void movemode::updateRoleAnimation()
{
	MoveModeRoleAnimation();
	updateAnimationTimer();
}

void movemode::updateAnimationTimer()
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->setInterval(100);
	connect(updateTimer, &QTimer::timeout, this, &movemode::MoveModeRoleAnimation);
	updateTimer->start();
}

void movemode::MoveModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	roleLabel->resize(200, 200);	//设置窗口大小
	roleLabel->setStyleSheet(qcut + QString("background-image:url(:/lalala/dogs/lalala/lalala (%1).png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 18;	//循环展示背景图片
}

void movemode::returnNormalMode()
{
	static int clickAreaX, clickAreaY;
	normalmode* n = new normalmode();
	clickAreaX = this->x();
	clickAreaY = this->y();
	n->move(clickAreaX - 35, clickAreaY + 35);
	n->show();
	this->close();
}

bool movemode::eventFilter(QObject* watched, QEvent* ev)
{
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	//判断鼠标左键按下
	static QPoint clickArea;
	
	if (ev->type() == QEvent::MouseButtonPress)
	{
		clickArea = mouseev->globalPos() - this->pos();
	}
	else if (ev->type() == QEvent::MouseMove && mouseev->buttons() & Qt::MouseButton::LeftButton)
	{
		this->move(mouseev->globalPos() - clickArea);
	}
	if (ev->type() == QEvent::MouseButtonRelease)
	{
		returnNormalMode();
	}
	return false;
}

movemode::~movemode()
{
	
}

