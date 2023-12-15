#include "game_main.h"
#include "crymode.h"

game_main::game_main(QWidget* parent) 
    : widget(parent)
    , currentFrame(0)
    , lastObstacleX(750)
    , characterX(50)
    , characterY(0)
    , isJumping(false)
    , jumpAngle(0.0)
{
    setAttribute(Qt::WA_DeleteOnClose);
    widget::WidgetsParameter();
    this->resize(900, 400);
    updateTimer();
}

void game_main::updateTimer()
{
    QTimer* animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &game_main::updateAnimation);
    animationTimer->start(36);
}

void game_main::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPixmap background(":/game_background/dogs/game_background/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), background);

    QPixmap frame(QString(":/game_run/dogs/game_run/r (%1).png").arg(currentFrame));
    painter.drawPixmap(50, this->height() - frame.height() - 6 - characterY, frame);

    QPixmap obstaclePixmap(":/game_obstacle/dogs/game_obstacle/obstacle.png");
    for (const Obstacle& obstacle : obstacles) {
        painter.drawPixmap(obstacle.x, 296, obstaclePixmap);
    }
}

void game_main::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space && !isJumping) {
        isJumping = true;
        jumpAngle = 0.0;
    }
}

void game_main::gotoCrymode()
{
    static int clickAreaX, clickAreaY;
    crymode* c = new crymode();
    clickAreaX = this->x();
    clickAreaY = this->y();
    c->move(clickAreaX + 310, clickAreaY + 100);
    c->show();
    this->close();
}


void game_main::updateAnimation() 
{
    currentFrame = (currentFrame + 1) % 16;

    auto it = obstacles.begin();
    while (it != obstacles.end()) {
        it->x -= obstacleSpeed;
        if (it->x < -100) {
            it = obstacles.erase(it); // 删除离开屏幕的障碍物
        }
        else {
            ++it;
        }
    }

    // 检查最后一个障碍物是否已经过了 x=600
    if (!obstacles.isEmpty() && obstacles.last().x <= 600) {
        lastObstacleX = obstacles.last().x;
    }

    // 随机生成新的障碍物
    if (lastObstacleX <= 750 && QRandomGenerator::global()->bounded(100) < 5) { // 5% 概率
        Obstacle newObstacle;
        newObstacle.x = 1000;
        obstacles.append(newObstacle); // 添加新障碍物
        lastObstacleX = 1000; // 更新最后一个障碍物的位置
    }

    int characterRightEdge = characterX + characterWidth; // 人物的最右边缘
    for (const Obstacle& obstacle : obstacles) {
        int obstacleLeftEdge = obstacle.x; // 障碍物的最左边缘
        int obstacleRightEdge = obstacle.x + obstacleWidth; // 障碍物的最右边缘

        int obstacleHeight = 100;
        bool aboveObstacle = characterY > obstacleHeight;

        if (characterRightEdge >= obstacleLeftEdge && characterRightEdge <= obstacleRightEdge && !aboveObstacle) {
            gotoCrymode(); // 检测到碰撞
            break;
        }
    }

    if (isJumping) {
        jumpAngle += 10.0;
        if (jumpAngle > 180.0) {
            isJumping = false;
            jumpAngle = 0.0;
            characterY = 0;
        }
        else {
            characterY = qSin(qDegreesToRadians(jumpAngle)) * jumpHeight;
        }
    }

    update(); // 触发重绘
}



game_main::~game_main()
{
}
