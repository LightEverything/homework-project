/**
   懒得锁帧了，看机器情况调吧
    用的qt版本5.12
**/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
