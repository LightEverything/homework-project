#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QMainWindow>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QVector>
#include <QTimer>
#include <QBrush>
#include <QLabel>
#include <QPoint>
#include <QRect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent* e) override;
    void keyPressEvent(QKeyEvent* e) override;
    void paintEvent(QPaintEvent* e) override;

private:

    // 枚举方向
    enum direction
    {
        up,
        down,
        right,
        left
    };

    // 枚举模式
    enum mode
    {
        startScene,
        endScene,
        gameScene
    };

    bool            isCrashRect(const QRect& x,  const QRect& y) const;
    bool 		    isPointIn(const QPoint& point, const QRect& rect) const;
    bool 	        isWall() const;
    bool 		    isBody() const;
    void 		    eatFood() ;

    // 懒得隐藏数据了，将就点看吧
    Ui::MainWindow *ui;
    QVector<QPoint> snake;
    QPoint          food;
    int 			timer;
    int 			backTimer;
    int 			updateTimer;
    int 			rectLen;
    int 			movedLen;
    int 			foodLen;
    int 			score;
    int 			imagePosx;
    int 			imagePosy;
    direction		dire;
    mode			gameMode;
    QPoint          startPoint;
    QColor			snakeColor;
    QColor			foodColor;
    QPixmap*		image;

    const int 		backMovePixel = 3;
    const int 		gameEasy = 300;
    const int       gameMid  = 100;
    const int 		gameDiff = 20;

signals:
    void 			startGame();
    void 			endGame();
};

#endif // MAINWINDOW_H
