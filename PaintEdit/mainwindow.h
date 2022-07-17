#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "drawingboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool useErase();
    bool changePenColor();
    bool clearDrawBoard();
private:
    Ui::MainWindow *ui;

    DrawingBoard* drawBoard;
    QPen          pen;
};
#endif // MAINWINDOW_H
