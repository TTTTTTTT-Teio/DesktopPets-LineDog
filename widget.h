#pragma once

#include <QtWidgets/QWidget>

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    void WidgetsParameter();    //设置窗口参数
    void ShadowEffect(); //设置背景阴影
    ~widget();

private:
};
