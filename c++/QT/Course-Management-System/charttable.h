/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       charttable.h
 * @brief      实现对qt的图表进行封装，将其写入一个控件中
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/20
 * @history
 *****************************************************************************/

#ifndef CHARTTABLE_H
#define CHARTTABLE_H


#include <QWidget>
#include <QChart>
#include <QPieSeries>
#include <QStringList>

#include "coursenode.h"

// 这个宏定义约等于 using QChart::~;
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class ChartTable;
}

/**
 * @brief ChartTable 自定义一个用于容纳QT图表的控件
 */
class ChartTable : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ChartTable 是一个构造函数，将list用图表的方式表示
     * @param list 是链表指针，根据这个指针构造图表
     * @param parent 用于QWidget初始化，并且绑定对象对象树
     */
    explicit ChartTable(CourseList* list, QWidget *parent = nullptr);
    ~ChartTable();

private:
    Ui::ChartTable *ui;

    CourseList* list; ///< 链表的指针
    /**
     * @brief setCourseStatusTable 函数功能是设置课程性质
     */
    void setCourseStatusTable();
    /**
     * @brief setTeacherNameTable  函数功能是设置老师名字
     */
    void setTeacherNameTable();
    /**
     * @brief setManagemetTable  函数功能是设置管理单位
     */
    void setManagemetTable();
};

#endif // CHARTTABLE_H
