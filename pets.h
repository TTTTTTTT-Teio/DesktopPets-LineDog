#pragma once

#include <QWidget>
#include<QPixmap>
#include<Qlabel>
class petsWidget  : public QWidget
{
	Q_OBJECT

public:
	petsWidget(QWidget *parent=nullptr);
	void updateRoleAnimation();	//贴图循环播放
	void updateAnimation();	//更新动画
	void ShadowEffect(); //设置背景阴影
	bool eventFilter(QObject* watched, QEvent* ev)override;	//左键点击拖动窗口
	~petsWidget();
private:
	QLabel* roleLabel;
	int8_t curFrame;	//当前图片
};
