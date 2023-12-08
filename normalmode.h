#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include "widget.h"

class normalmode : public widget
{
	Q_OBJECT

public:
	normalmode(QWidget* parent = nullptr);

	bool eventFilter(QObject* watched, QEvent* ev)override;	//左键敲击事件
	void openMenu();

	~normalmode();

protected:
	void updateRoleAnimation();	//选择播放的动作
	void updateAnimationTimer();	//更新动画
	void gotoDirtymodeTimer();
	void NormalModeRoleAnimation();	//常态化背景贴图
	void gotoMovemode();
	void gotoDirtymode();
	void gotoWashmode();
	void closeWidget();

private:
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};