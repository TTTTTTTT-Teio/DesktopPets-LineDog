#include "normalmode.h"
#include "movemode.h"
#include "qtimer.h"
#include "QMovie"
#include "QMouseEvent"
#include "Qmenu"

normalmode::normalmode(QWidget* parent)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	ui.setupUi(this);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	normalmode::updateRoleAnimation();
	this->installEventFilter(this);
}

void normalmode::updateRoleAnimation()
{
	NormalModeRoleAnimation();
	updateAnimationTimer();
}

void normalmode::updateAnimationTimer()
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->start(100);
	updateTimer->callOnTimeout(this, &normalmode::NormalModeRoleAnimation);
}

void normalmode::NormalModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	roleLabel->resize(200, 200);	//设置窗口大小
	roleLabel->setStyleSheet(qcut + QString("background-image:url(:/nuli/dogs/nuli/(%1).png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 37;	//循环展示背景图片
}

bool normalmode::eventFilter(QObject* watched, QEvent* ev)
{
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	//判断鼠标左键按下
	static int clickAreaX,clickAreaY;
	if (ev->type() == QEvent::MouseButtonPress && mouseev->buttons() & Qt::MouseButton::LeftButton)
	{
		clickAreaX = this->x();
		clickAreaY = this->y();
		movemode* m = new movemode();
		m->move(clickAreaX + 35, clickAreaY - 35);
		m->show();
		this->close();
	}
	if (ev->type() == QEvent::MouseButtonPress && mouseev->buttons() & Qt::MouseButton::RightButton)
	{
		QMenu* menu = new QMenu;
		QAction* saveaction = new QAction;
		saveaction->setText("按钮1");
		menu->addAction(saveaction);
		menu->exec(QCursor::pos());
		return true;
	}
	return false;
}

normalmode::~normalmode()
{

}
