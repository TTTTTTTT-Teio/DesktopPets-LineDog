#pragma once

#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include "widget.h"

class washmode : public widget
{
	Q_OBJECT

public:
	washmode(QWidget* parent = nullptr);

	~washmode();

protected:
	void updateRoleAnimation();	//选择播放的动作
	void updateAnimationTimer();	//更新动画
	void WashModeRoleAnimation();	//常态化背景贴图
	void returnNormalModeTimer();
	void returnNormalMode();	//回到常态模式

private:
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};