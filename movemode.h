#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include "widget.h"
#include "ui_widget.h"

class movemode : public widget
{
	Q_OBJECT

public:
	movemode(QWidget* parent = nullptr);

	bool eventFilter(QObject* watched, QEvent* ev)override;	//左键敲击事件

	~movemode();

protected:
	void updateRoleAnimation();	//选择播放的动作
	void updateAnimationTimer();	//更新动画
	void MoveModeRoleAnimation();	//常态化背景贴图
	void returnNormalMode();	//回到常态模式

private:
	Ui::widgetClass ui;
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};