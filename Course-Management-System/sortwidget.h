/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       sortwidget.h
 * @brief      这是一个控件，用来排序的选项
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/21
 * @history
 *****************************************************************************/

#ifndef SORTWIDGET_H
#define SORTWIDGET_H

#include <QWidget>

#include "sortm.h"

namespace Ui {
class SortWidget;
}

/**
 * @brief The SortWidget class 这是一个控件类，用于改变用户的排序方式
 * @note 默认排序方式是课程名字
 */
class SortWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief SortWidget 这是一个构造函数
     * @param now 现在的排序方式，默认将会以课程名字排序
     * @param parent 用于QWidget初始化，并且绑定对象对象树
     */
    explicit SortWidget(Sortm now = course_name,QWidget *parent = nullptr);
    ~SortWidget();

private:
    Ui::SortWidget *ui;
    Sortm now; ///< 当前状况
signals:
    /**
     * @brief sortSignal 这是一个信号函数,给出选中的选项
     * @param sortsignal 这代表选中的选项
     */
    void sortSignal(Sortm sortsignal);
};

#endif // SORTWIDGET_H
