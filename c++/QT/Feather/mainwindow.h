#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "setting.h"
#include "textinput.h"
#include <QMainWindow>
#include <QFile>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QFile* openWrite();
    void writeData();
    void readData();
    void setNewTab();
    void setTextWidget(TextInput*);
    void setFont();
    void init();
    void closeTab();
private:
    Ui::MainWindow *ui;
    Setting gbalSet;
};
#endif // MAINWINDOW_H
