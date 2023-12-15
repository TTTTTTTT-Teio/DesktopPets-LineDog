#pragma once

#include <QRandomGenerator>
#include <QGuiApplication>
#include <QScreen>
#include <QtWidgets/QWidget>
#include <Qlabel>
#include <QPixmap>
#include "qtimer.h"
#include "widget.h"

class automovemode : public widget
{
	Q_OBJECT

public:
	automovemode(QWidget* parent = nullptr, int prevX = 0, int prevY = 0);
	~automovemode();

private:
	void updateRoleAnimation();
	void moveWindowLeft();
	void moveWindowRight();
	void LeftMoveWindowToPosition(int targetX, int targetY);
	void RightMoveWindowToPosition(int targetX, int targetY);
	void LeftAutoMoveupdateAnimationTimer();	//更新动画
	void RightAutoMoveupdateAnimationTimer();	//更新动画
	void LeftAutoMoveModeRoleAnimation();
	void RightAutoMoveModeRoleAnimation();
	void returnNormalMode(int targetX, int targetY);	//回到常态模式

private:
	QLabel* roleLabel;
	int8_t curFrame;	
	int targetX;
	int targetY;
};

