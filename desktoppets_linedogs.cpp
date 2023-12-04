#include "desktoppets_linedogs.h"
#include "qtimer.h"
#include "QMovie"
#include "QGraphicsDropShadowEffect"
#include "QMouseEvent"

DesktopPets_LineDogs::DesktopPets_LineDogs(QWidget *parent)
    : QWidget(parent)
    , roleLabel(new QLabel(this))
    , curFrame(0)
{
    ui.setupUi(this);
	//窗口属性
	setWindowFlags(Qt::WindowType::FramelessWindowHint);	//无边框
	setAttribute(Qt::WA_TranslucentBackground);	//背景透明
	roleLabel->resize(200, 200);

	updateRoleAnimation(Normal);
	ShadowEffect();

	this->installEventFilter(this);
}

void DesktopPets_LineDogs::updateRoleAnimation(PetsMode petsmode)
{
	switch (petsmode) {
	case Normal:
		NormalModeRoleAnimation();
		updateAnimationTimer(Normal);
		break;
	case Move:
		MoveModeRoleAnimation();
		updateAnimationTimer(Move);
		break;
	}
}

void DesktopPets_LineDogs::updateAnimationTimer(PetsMode petsmode)
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	if (petsmode == Normal) {
		updateTimer->start(100);
		updateTimer->callOnTimeout(this, &DesktopPets_LineDogs::NormalModeRoleAnimation);
	}
	else if (petsmode == Move) {
		updateTimer->stop();
		updateTimer->start(500);
		updateTimer->callOnTimeout(this, &DesktopPets_LineDogs::MoveModeRoleAnimation);
	}
}

void DesktopPets_LineDogs::ShadowEffect()
{
	//窗口设置阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(230, 230, 230, 220));
	effect->setBlurRadius(1);
	this->setGraphicsEffect(effect);
}

void DesktopPets_LineDogs::NormalModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	roleLabel->setStyleSheet(qcut + QString("background-image:url(:/nuli/dogs/nuli/(%1).png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 37;	//循环展示背景图片
}

void DesktopPets_LineDogs::MoveModeRoleAnimation()
{
	roleLabel->clear();
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	roleLabel->setStyleSheet(qcut + QString("background-image:url(:/lalala/dogs/lalala/lalala (%1).png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 18;	//循环展示背景图片
}

bool DesktopPets_LineDogs::eventFilter(QObject* watched, QEvent* ev)
{
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	//判断鼠标左键按下
	static QPoint clickArea;
	if (ev->type() == QEvent::MouseButtonPress)
	{
		updateRoleAnimation(Move);
		clickArea = mouseev->globalPos() - this->pos();
	}
	else if (ev->type() == QEvent::MouseMove && mouseev->buttons() & Qt::MouseButton::LeftButton)
	{
		this->move(mouseev->globalPos() - clickArea);
	}
	return false;
}

DesktopPets_LineDogs::~DesktopPets_LineDogs()
{

}
