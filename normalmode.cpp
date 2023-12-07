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

void normalmode::gotoMovemode()
{
	static int clickAreaX, clickAreaY;
	clickAreaX = this->x();
	clickAreaY = this->y();
	movemode* m = new movemode();
	m->move(clickAreaX + 35, clickAreaY - 35);
	m->show();
	this->close();
}

void normalmode::closeWidget()
{
	this->close();
}

void normalmode::openMenu()
{
	QMenu* menu = new QMenu;

	QAction* closeAction = new QAction;
	closeAction->setText("关闭");
	connect(closeAction,&QAction::triggered,this,&normalmode::closeWidget);

	menu->addAction(closeAction);
	menu->exec(QCursor::pos());
}

bool normalmode::eventFilter(QObject* watched, QEvent* ev)
{
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	//判断鼠标左键按下

	if (ev->type() == QEvent::MouseButtonPress && mouseev->buttons() & Qt::MouseButton::LeftButton)
	{
		gotoMovemode();
	}
	if (ev->type() == QEvent::MouseButtonPress && mouseev->buttons() & Qt::MouseButton::RightButton)
	{
		openMenu();
	}
	return false;
}

normalmode::~normalmode()
{

}
