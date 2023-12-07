#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include "widget.h"
#include "ui_widget.h"

class normalmode : public widget
{
	Q_OBJECT

public:
	normalmode(QWidget* parent = nullptr);

	bool eventFilter(QObject* watched, QEvent* ev)override;	//左键敲击事件

	~normalmode();

protected:
	void updateRoleAnimation();	//选择播放的动作
	void updateAnimationTimer();	//更新动画
	void NormalModeRoleAnimation();	//常态化背景贴图
	void gotoMovemode();
	void closeWidget();
	void openMenu();

private:
	Ui::widgetClass ui;
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};