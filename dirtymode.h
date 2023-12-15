#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include "qtimer.h"
#include "QMouseEvent"
#include "Qmenu"
#include "widget.h"

class dirtymode : public widget
{
	Q_OBJECT

public:
	dirtymode(QWidget* parent = nullptr);
	~dirtymode();

protected:
	bool eventFilter(QObject* watched, QEvent* ev)override;	//左键敲击事件

private:
	void updateRoleAnimation();	//选择播放的动作
	void updateAnimationTimer();	//更新动画
	void DirtyModeRoleAnimation();	//常态化背景贴图
	void gotoWashmode();
	void closeWidget();
	void openMenu();

private:
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};