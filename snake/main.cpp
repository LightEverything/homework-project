/**
   懒得锁帧了，看机器情况调吧
   怕你们那边不好调，我就没分多文件了
   注释写得挺清楚了,根据变量名调整就可以了
    注意尽量别改变量名
    用的qt版本5.12
    用科科换的hhhh
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
