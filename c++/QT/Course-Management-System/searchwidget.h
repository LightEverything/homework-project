/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       searchwidget.h
 * @brief      这是一个控件，用来处理模糊搜索的字符串和选项
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/21
 * @history
 *****************************************************************************/
#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

#include "sortm.h"

namespace Ui {
class SearchWidget;
}

/**
 * @brief The SearchWidget class 这是一个控件，用来处理模糊搜索的字符串和选项
 */
class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief SearchWidget 是一个构造函数
     * @param parent用于QWidget初始化，并且绑定对象对象树
     */
    explicit SearchWidget(QWidget *parent = nullptr);
    ~SearchWidget();

private:
    Ui::SearchWidget *ui;

    Sortm	default_option_ = course_name; ///< 默认选中的选项

signals:
    /**
     * @brief searchItem 这是一个信号函数
     * @param items 这是一个选项
     * @param str 这是一个临时对象的拷贝
     * @note  信号功能是传递选项和搜索用的字符串，注意这里返回的是QString的临时对象\n这是是对用户友好，防止用户忘记释放指针导致内存泄漏
     */
    void searchItem(Sortm items, QString str);
};

#endif // SEARCHWIDGET_H
