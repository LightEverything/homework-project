/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       mainwindow.h
 * @brief      主界面类文件，是所有控件对象的根对象，负责调控控件和内存释放
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/21
 * @history
 *****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QByteArray>
#include <QTextStream>

#include "coursenode.h"
#include "listtable.h"
#include "helper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/**
 * @brief The MainWindow class 主界面类文件，是所有控件对象的根对象，负责调控控件和内存释放
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow 构造函数和析构函数
     * @param parent 用于QWidget初始化，并且绑定对象对象树
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui; ///< xml内控件初始化
    CourseList*     list_; ///< 链表
    QString			file_; ///< 文件名字
    QIcon			icon_; ///< 图标
    QIcon 			new_icon_; ///< 新建图标

    /**
     * @brief openFile 函数功能是打开一个文件
     */
    void openFile();
    /**
     * @brief createList 根据文件名创建链表
     * @param fileName 是文件名字
     */
    void createList(const QString& fileName);
    /**
     * @brief changeToTable 函数功能是切换到Table页面
     */
    void changeToTable();
    /**
     * @brief saveFile 函数功能是将表格保存到文件
     */
    void saveFile();
    /**
     * @brief revalue 函数功能是将表格还原
     */
    void revalue();
    /**
     * @brief newFile 函数功能是新建一个文件
     */
    void newFile();
    /**
     * @brief reWelcomeWidget 函数功能是释放链表指针并且回到主界面
     */
    void reWelcomeWidget();
};

#endif // MAINWINDOW_H
