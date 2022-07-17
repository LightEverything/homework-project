#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , updateTimer(20)
    , rectLen(20)
    , movedLen(20)
    , foodLen(10)
    , score(0)
    , imagePosx(0)
    , imagePosy(0)
    , dire(right)
    , gameMode(startScene)
    , startPoint(10, 10)
    , snakeColor(Qt::gray)
    , foodColor(Qt::red)
    , image(new QPixmap(":/back.jpg"))
{
    // 别动，初始化
    ui->setupUi(this);
    ui->gameScene->setCurrentWidget(ui->start);
    setWindowTitle("Snake");
    setCentralWidget(ui->gameScene);

    // 背景计时器
    backTimer = startTimer(100);

    connect(ui->pbStartGame, &QPushButton::clicked, this, [=]()
        {
            emit startGame();
        });

    connect(this, &MainWindow::startGame, this, [=]()
        {
            ui->gameScene->setCurrentWidget(ui->game);
            dire = right;
            score = 0;
            ui->lbscore->setText(QString("score: %1").arg(score));

            // 随机food
            food.setX(QRandomGenerator::global()->bounded(width() - foodLen * 2));
            food.setY(QRandomGenerator::global()->bounded(height() - foodLen * 2));

            gameMode = gameScene;
            snake.push_back(startPoint);

            timer = startTimer(updateTimer);
        });

    connect(this, &MainWindow::endGame, this, [=]()
        {
            killTimer(timer);
            snake.clear();
            gameMode = endScene;
            ui->gameScene->setCurrentWidget(ui->end);
        });

    connect(ui->pbTryAgain, &QPushButton::clicked, this, [=]()
    {
        ui->gameScene->setCurrentWidget(ui->game);
        emit startGame();
    });

    connect(ui->pbset, &QPushButton::clicked, this, [=]()
    {
        ui->gameScene->setCurrentWidget(ui->set);

        if (updateTimer == gameEasy)
            ui->rbEasy->setChecked(true);
        else if (updateTimer == gameMid)
            ui->rbMid->setChecked(true);
        else
            ui->rbDiffi->setChecked(true);

    });

    connect(ui->pbsave, &QPushButton::clicked, this, [=]()
    {
        if (ui->rbEasy->isChecked())
            updateTimer = gameEasy;
        else if (ui->rbMid->isChecked())
            updateTimer = gameMid;
        else
            updateTimer = gameDiff;
        ui->gameScene->setCurrentWidget(ui->start);
    });
}

MainWindow::~MainWindow()
{
    // 释放变量
    delete ui;
}

// 计时器事件
void MainWindow::timerEvent(QTimerEvent* e)
{
    if (e->timerId() == backTimer)
    {
       imagePosx -= backMovePixel;
       imagePosy -= backMovePixel;
       imagePosx %= width();
       imagePosy %= height();

       update();
    }
    if (e->timerId() == timer)
    {
        // pre指的是前一个方块位置
        auto pre = snake[0];

        // 先进行移动
        switch (dire)
        {
        case up:
            snake[0].setX(snake[0].rx());
            snake[0].setY(snake[0].ry() - movedLen);
            break;
        case down:
            snake[0].setX(snake[0].rx());
            snake[0].setY(snake[0].ry() + movedLen);
            break;
        case left:
            snake[0].setX(snake[0].rx() - movedLen);
            snake[0].setY(snake[0].ry());
            break;
        case right:
            snake[0].setX(snake[0].rx() + movedLen);
            snake[0].setY(snake[0].ry());
            break;
        }

        // 移动身体
        for (int i = 1; i < snake.size(); i++)
        {
            auto tmp = snake[i];
            snake[i] = pre;
            pre = tmp;
        }

        // 吃到食物
        if(isCrashRect(QRect(snake[0].x(), snake[0].y(), rectLen, rectLen),
               QRect(food.x(), food.y(), foodLen, foodLen)) ||
        isCrashRect(QRect(food.x(), food.y(), foodLen, foodLen),
                QRect(snake[0].x(), snake[0].y(), rectLen, rectLen))  )
        {
            eatFood();
        }

        // 游戏结束(撞墙或者是撞身体)
        if (isWall() || isBody())
        {
            emit endGame();
        }

        update();
    }
    return QMainWindow::timerEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    switch(e->key())
    {
    case Qt::Key_Up:
        if (dire != down)
            dire = up;
        break;
    case Qt::Key_Down:
        if (dire != up)
            dire = down;
        break;
    case Qt::Key_Left:
        if (dire != right)
            dire = left;
        break;
    case Qt::Key_Right:
        if (dire != left)
            dire = right;
        break;
    case Qt::Key_Q:
        break;
    default:
        break;
    }
    return QMainWindow::keyPressEvent(e);
}

void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.drawPixmap(imagePosx, imagePosy, *image);

    if (gameMode == gameScene)
    {
        QPainter pt(this);
        pt.setBrush(QBrush(snakeColor));
        // 画蛇
        for (auto item : snake)
            pt.drawRect(item.x(), item.y(), rectLen, rectLen);

        pt.setBrush(QBrush(foodColor));
        // 画食物
        pt.drawEllipse(food.x(), food.y(), foodLen, foodLen);
        pt.setBrush(QBrush(Qt::black));
        // 画得分
        ui->lbscore->setText(QString("score: %1").arg(score));
    }

    return QMainWindow::paintEvent(e);
}

// 检测盒体碰撞
bool MainWindow::isCrashRect(const QRect & x, const QRect& y) const
{
    // 四个点
    if (isPointIn(x.topLeft(), y) ||
            isPointIn(x.bottomLeft(), y) ||
            isPointIn(x.topRight(), y) ||
            isPointIn(x.bottomRight(), y))
        return true;
    else
        return false;
}

// 矩形内是否包括点
bool MainWindow::isPointIn(const QPoint& point, const QRect& rect) const
{
    if (point.x() >= rect.topLeft().x() &&
            point.x() <= rect.topRight().x() &&
            point.y() >= rect.topLeft().y() &&
            point.y() <= rect.bottomLeft().y())
        return true;
    else
        return false;
}

void MainWindow::eatFood()
{
    score++;

    food.setX(QRandomGenerator::global()->bounded(560));
    food.setY(QRandomGenerator::global()->bounded(380));

    snake.push_back(QPoint(snake[snake.size() - 1]));
}

bool MainWindow::isWall() const
{
    if (snake[0].x() <= 0 || snake[0].x() >= width() ||
        snake[0].y() <= 0 || snake[0].y() >= height())
        return true;

    return false;
}

bool MainWindow::isBody() const
{
    for (int i = 2; i < snake.size(); i++)
    {
        if (isCrashRect(QRect(snake[i].x(), snake[i].y(), rectLen, rectLen),
                        QRect(snake[0].x(), snake[0].y(), rectLen, rectLen)))
            return true;
    }

    return false;
}
