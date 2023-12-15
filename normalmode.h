#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include <QRandomGenerator>
#include "widget.h"
#include "qtimer.h"
#include "QMouseEvent"
#include "Qmenu"

class normalmode : public widget
{
	Q_OBJECT

public:
	normalmode(QWidget* parent = nullptr);
	~normalmode();

protected:
	bool eventFilter(QObject* watched, QEvent* ev)override;	//左键敲击事件
	void openMenu();

private:
	void updateRoleAnimation();	//选择播放的动作
	void updateAnimationTimer();	//更新动画
	void gotoDirtymodeTimer();
	void gotoAutoMovemodeTimer();
	void Probability();
	void NormalModeRoleAnimation();	//常态化背景贴图
	void gotoMovemode();
	void gotoDirtymode();
	void gotoWashmode();
	void gotoGamemode();
	void gotoAutoMovemode();
	void closeWidget();

private:
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};