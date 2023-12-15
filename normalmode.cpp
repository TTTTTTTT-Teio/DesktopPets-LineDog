#include "normalmode.h"
#include "movemode.h"
#include "dirtymode.h"
#include "washmode.h"
#include "game_main.h"
#include "automovemode.h"


normalmode::normalmode(QWidget* parent)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	setAttribute(Qt::WA_DeleteOnClose);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	normalmode::updateRoleAnimation();
	this->installEventFilter(this);
}

void normalmode::updateRoleAnimation()
{
	NormalModeRoleAnimation();
	updateAnimationTimer();
	gotoDirtymodeTimer();
	gotoAutoMovemodeTimer();
}

void normalmode::updateAnimationTimer()
{
	//定时器更新动画（循环一次背景图片更新一次）
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->setInterval(100);
	connect(updateTimer, &QTimer::timeout, this, &normalmode::NormalModeRoleAnimation);
	updateTimer->start();
}

void normalmode::gotoDirtymodeTimer()
{
	QTimer* dirtyTimer = new QTimer(this);
	dirtyTimer->setTimerType(Qt::PreciseTimer);
	dirtyTimer->setSingleShot(true);
	dirtyTimer->setInterval(/*600000*/6000000);
	connect(dirtyTimer,&QTimer::timeout,this,&normalmode::gotoDirtymode);
	dirtyTimer->start();
}

void normalmode::gotoAutoMovemodeTimer()
{
	QTimer* automoveTimer = new QTimer(this);
	automoveTimer->setTimerType(Qt::PreciseTimer);
	automoveTimer->setInterval(1000);
	connect(automoveTimer, &QTimer::timeout, this, &normalmode::Probability);
	automoveTimer->start();
}

void normalmode::Probability() {
	int randomNumber = QRandomGenerator::global()->bounded(200);
	if (randomNumber == 0) {
		gotoAutoMovemode();
	}
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

void normalmode::gotoDirtymode()
{
	static int clickAreaX, clickAreaY;
	clickAreaX = this->x();
	clickAreaY = this->y();
	dirtymode* d = new dirtymode();
	d->move(clickAreaX + 35, clickAreaY - 100);
	d->show();
	this->close();
}

void normalmode::gotoWashmode()
{
	static int clickAreaX, clickAreaY;
	clickAreaX = this->x();
	clickAreaY = this->y();
	washmode* wa = new washmode();
	wa->move(clickAreaX + 50, clickAreaY - 50);
	wa->show();
	this->close();
}

void normalmode::gotoGamemode()
{
	static int clickAreaX, clickAreaY;
	clickAreaX = this->x();
	clickAreaY = this->y();
	game_main* g_m = new game_main();
	g_m->move(clickAreaX - 250, clickAreaY - 200);
	g_m->show();
	this->close();
}

void normalmode::gotoAutoMovemode()
{
	static int clickAreaX, clickAreaY;
	clickAreaX = this->x();
	clickAreaY = this->y();
	automovemode* am = new automovemode(nullptr, clickAreaX, clickAreaY);
	am->move(clickAreaX + 30, clickAreaY - 120);
	am->show();
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

	QAction* gotoWashAction = new QAction;
	gotoWashAction->setText("洗澡");
	connect(gotoWashAction, &QAction::triggered, this, &normalmode::gotoWashmode);

	QAction* gotoGameAction= new QAction;
	gotoGameAction->setText("玩耍");
	connect(gotoGameAction, &QAction::triggered, this, &normalmode::gotoGamemode);

	menu->addAction(closeAction);
	menu->addAction(gotoWashAction);
	menu->addAction(gotoGameAction);
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
