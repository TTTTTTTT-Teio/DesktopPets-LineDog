#pragma once

#include <QtWidgets/QWidget>
#include "ui_desktoppets_linedogs.h"
#include <QWidget>
#include<QPixmap>
#include<Qlabel>

enum PetsMode { Normal = 0, Move = 1 };

class DesktopPets_LineDogs : public QWidget
{
    Q_OBJECT

public:
    DesktopPets_LineDogs(QWidget *parent = nullptr);
	void updateRoleAnimation(PetsMode petsmode);	//选择播放的动作
	void updateAnimationTimer(PetsMode petsmode);	//更新动画
	void ShadowEffect(); //设置背景阴影

	//贴图循环播放
	void NormalModeRoleAnimation();
	void MoveModeRoleAnimation();

	bool eventFilter(QObject* watched, QEvent* ev)override;	//左键点击拖动窗口
    ~DesktopPets_LineDogs();

private:
    Ui::DesktopPets_LineDogsClass ui;
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};
