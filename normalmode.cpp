#include "normalmode.h"
#include "qtimer.h"

normalmode::normalmode(QWidget* parent)
	:widget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
{
	ui.setupUi(this);
	widget::WidgetsParameter();
	widget::ShadowEffect();
	updateRoleAnimation();
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
	roleLabel->resize(200, 200);
	roleLabel->setStyleSheet(qcut + QString("background-image:url(:/nuli/dogs/nuli/(%1).png);").arg(curFrame));	//窗口贴上背景图片
	curFrame = (curFrame + 1) % 37;	//循环展示背景图片
}

normalmode::~normalmode()
{

}
