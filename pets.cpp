#include "pets.h"
#include "qtimer.h"
#include "QMovie"
#include "QGraphicsDropShadowEffect"
#include "QMouseEvent"

petsWidget::petsWidget(QWidget *parent)
	: QWidget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	//窗口属性
	setWindowFlags(Qt::WindowType::FramelessWindowHint);	//无边框
	setAttribute(Qt::WA_TranslucentBackground);	//背景透明
	roleLabel->resize(200, 200);
	
	updateRoleAnimation();
	updateAnimation();
	ShadowEffect();

	this->installEventFilter(this);
}

void petsWidget::updateRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	roleLabel->setStyleSheet(qcut + QString("background-image:url(:/lalala/dogs/lalala/lalala (%1).png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1)%17;	//循环展示背景图片
}

void petsWidget::updateAnimation()
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->callOnTimeout(this, &petsWidget::updateRoleAnimation);
	updateTimer->start(100);
}

void petsWidget::ShadowEffect()
{
	//窗口设置阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(230, 230, 230, 220));
	effect->setBlurRadius(1);
	this->setGraphicsEffect(effect);
}

bool petsWidget::eventFilter(QObject* watched, QEvent* ev)
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
		this->move(mouseev->globalPos()-clickArea);
	}
	return false;
}



petsWidget::~petsWidget()
{

}
