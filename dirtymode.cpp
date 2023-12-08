#include "normalmode.h"
#include "dirtymode.h"
#include "washmode.h"
#include "qtimer.h"
#include "QMovie"
#include "QMouseEvent"
#include "Qmenu"

dirtymode::dirtymode(QWidget* parent)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	setAttribute(Qt::WA_DeleteOnClose);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	dirtymode::updateRoleAnimation();
	this->installEventFilter(this);
}

void dirtymode::updateRoleAnimation()
{
	DirtyModeRoleAnimation();
	updateAnimationTimer();
}

void dirtymode::updateAnimationTimer()
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->setInterval(100);
	connect(updateTimer, &QTimer::timeout, this, &dirtymode::DirtyModeRoleAnimation);
	updateTimer->start();
}

void dirtymode::DirtyModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	QString qpos("background-position: bottom left;");
	roleLabel->resize(200, 200);	//设置窗口大小
	roleLabel->setStyleSheet(qpos + qcut + QString("background-image:url(:/zangzangdogs/dogs/zangzangdogs/%1.png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 21;	//循环展示背景图片
}

void dirtymode::gotoWashmode()
{
	static int clickAreaX, clickAreaY;
	clickAreaX = this->x();
	clickAreaY = this->y();
	washmode* wa = new washmode();
	wa->move(clickAreaX + 25, clickAreaY + 25);
	wa->show();
	this->close();
}

void dirtymode::closeWidget()
{
	this->close();
}

void dirtymode::openMenu()
{
	QMenu* menu = new QMenu;

	QAction* closeAction = new QAction;
	closeAction->setText("关闭");
	connect(closeAction, &QAction::triggered, this, &dirtymode::closeWidget);

	QAction* gotoWashAction = new QAction;
	gotoWashAction->setText("洗澡");
	connect(gotoWashAction, &QAction::triggered, this, &dirtymode::gotoWashmode);

	menu->addAction(closeAction);
	menu->addAction(gotoWashAction);
	menu->exec(QCursor::pos());
}

bool dirtymode::eventFilter(QObject* watched, QEvent* ev)
{
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	//判断鼠标左键按下

	if (ev->type() == QEvent::MouseButtonPress && mouseev->buttons() & Qt::MouseButton::RightButton)
	{
		openMenu();
	}
	return false;
}

dirtymode::~dirtymode()
{

}
