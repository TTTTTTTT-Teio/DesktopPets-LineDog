#include "normalmode.h"
#include "automovemode.h"

automovemode::automovemode(QWidget* parent, int prevX, int prevY)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	setAttribute(Qt::WA_DeleteOnClose);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	this->move(prevX, prevY);
	automovemode::updateRoleAnimation();
}

void automovemode::updateRoleAnimation()
{
	QRect screenRect = QGuiApplication::primaryScreen()->geometry();

	// 生成随机位置
	int randomX = QRandomGenerator::global()->bounded(screenRect.width() - 300);
	int randomY = QRandomGenerator::global()->bounded(screenRect.height() - 300);

	// 获取窗口在屏幕上的绝对位置
	QPoint globalPos = this->mapToGlobal(this->pos());
	int currentX = globalPos.x();

	// 检查随机位置是在左边还是右边
	if (randomX < currentX) {
		LeftAutoMoveModeRoleAnimation();
		LeftAutoMoveupdateAnimationTimer();
		LeftMoveWindowToPosition(randomX, randomY);
	}
	else if (randomX > currentX) {
		RightAutoMoveModeRoleAnimation();
		RightAutoMoveupdateAnimationTimer();
		RightMoveWindowToPosition(randomX, randomY);
	}
}

void automovemode::moveWindowLeft()
{
	int currentX = this->x();
	int currentY = this->y();

	if (currentX <= targetX) {
		this->move(targetX, targetY);
		returnNormalMode(targetX, targetY);
		return;
	}

	int deltaX = qMin(5, qAbs(currentX - targetX));
	int deltaY = (targetX != currentX) ? (targetY - currentY) * deltaX / qAbs(currentX - targetX) : 0;

	this->move(currentX - deltaX, currentY + deltaY);
}

void automovemode::moveWindowRight()
{
	int currentX = this->x();
	int currentY = this->y();

	if (currentX >= targetX) {
		this->move(targetX, targetY);
		returnNormalMode(targetX, targetY);
		return;
	}

	int deltaX = qMin(5, qAbs(targetX - currentX));
	int deltaY = (targetX != currentX) ? (targetY - currentY) * deltaX / qAbs(targetX - currentX) : 0;

	this->move(currentX + deltaX, currentY + deltaY);
}

void automovemode::LeftMoveWindowToPosition(int targetX, int targetY)
{
	this->targetX = targetX;
	this->targetY = targetY;

	QTimer* moveTimer = new QTimer(this);
	connect(moveTimer, &QTimer::timeout, this, &automovemode::moveWindowLeft);
	moveTimer->start(100);
}

void automovemode::RightMoveWindowToPosition(int targetX, int targetY)
{
	this->targetX = targetX;
	this->targetY = targetY;

	QTimer* moveTimer = new QTimer(this);
	connect(moveTimer, &QTimer::timeout, this, &automovemode::moveWindowRight);
	moveTimer->start(100); // 调整定时器间隔以控制移动速度
}

void automovemode::LeftAutoMoveupdateAnimationTimer()
{
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->setInterval(100);
	connect(updateTimer, &QTimer::timeout, this, &automovemode::LeftAutoMoveModeRoleAnimation);
	updateTimer->start();
}

void automovemode::RightAutoMoveupdateAnimationTimer()
{
	QTimer* updateTimer = new QTimer(this);
	updateTimer->setTimerType(Qt::PreciseTimer);
	updateTimer->setInterval(100);
	connect(updateTimer, &QTimer::timeout, this, &automovemode::RightAutoMoveModeRoleAnimation);
	updateTimer->start();
}

void automovemode::LeftAutoMoveModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	QString qpos("background-position: bottom left;");
	roleLabel->resize(200, 200);	//设置窗口大小
	roleLabel->setStyleSheet(qpos + qcut + QString("background-image:url(:/left_automove/dogs/left_automove/%1.png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 14;	//循环展示背景图片
}

void automovemode::RightAutoMoveModeRoleAnimation()
{
	QString qcut("background-repeat:no-repeat;");	//裁剪背景图片
	QString qpos("background-position: bottom left;");
	roleLabel->resize(200, 200);	//设置窗口大小
	roleLabel->setStyleSheet(qpos + qcut + QString("background-image:url(:/right_automove/dogs/right_automove/%1.png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 14;	//循环展示背景图片
}

void automovemode::returnNormalMode(int targetX, int targetY)
{
	normalmode* n = new normalmode();
	n->move(targetX, targetY);
	n->show();
	this->close();
}

automovemode::~automovemode()
{

}