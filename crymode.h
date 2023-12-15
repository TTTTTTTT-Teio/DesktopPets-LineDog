#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include "qtimer.h"
#include "widget.h"

class crymode : public widget
{
	Q_OBJECT

public:
	crymode(QWidget* parent = nullptr);
	~crymode();

private:
	void updateRoleAnimation();	//选择播放的动作
	void updateAnimationTimer();	//更新动画
	void CryModeRoleAnimation();	//常态化背景贴图
	void returnNormalModeTimer();
	void returnNormalMode();	//回到常态模式

private:
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};