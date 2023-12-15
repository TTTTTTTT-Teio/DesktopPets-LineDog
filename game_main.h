#pragma once

#include "widget.h"
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>
#include <QList>
#include <QtMath>
#include <QKeyEvent>

class game_main : public widget {
    Q_OBJECT

public:
    game_main(QWidget* parent = nullptr);
    ~game_main();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void updateAnimation();
    void updateTimer();
    void gotoCrymode();

private:
    struct Obstacle {
        int x;
    };
    int currentFrame;
    QList<Obstacle> obstacles;
    const int obstacleSpeed = 16;
    int lastObstacleX;
    const int characterWidth = 90;
    const int obstacleWidth = 40;
    int characterX;
    int characterY;
    bool isJumping;
    float jumpAngle;
    const int jumpHeight = 200;
};