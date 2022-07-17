// 注：qt自带内存回收,如果不带内存回收的话，建议使用智能指针代替裸指针
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
