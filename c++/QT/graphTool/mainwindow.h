#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QSettings>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>
#include "nodegraphscene.h"
#include "settingwidget.h"
#include "authorwidget.h"
#include "helperwidget.h"
#include "coffeewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openSettingWidget();
private:
    void getValue();
    void clearAll();
    void savePicture();
    void initSetting();
    void saveFile();
    void openFile();
    void allowMatrix();
    void canntMatrix();
    void openHelpWidget();

    Ui::MainWindow*  ui;
    // 设置
    QSettings*       setting = nullptr;
    NodeGraphScene   scene;
    sceneMode        mode;
};
#endif // MAINWINDOW_H
