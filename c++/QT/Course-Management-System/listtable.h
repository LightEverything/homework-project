/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       listtable.h
 * @brief      图像界面的核心，用于将链表用表格展示并且处理
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/20
 * @history
 *****************************************************************************/
#ifndef LISTTABLE_H
#define LISTTABLE_H

#include <QWidget>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>

#include "coursenode.h"
#include "sortwidget.h"
#include "searchwidget.h"
#include "charttable.h"
#include "netwidget.h"

namespace Ui {
class ListTable;
}

/**
 * @brief The ListTable class 是一个核心界面类, 用于将链表用表格展示并且处理
 * @note  这个类里面会存储一个临时的链表，以至于实现还原功能
 */
class ListTable : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ListTable 是一个构造函数
     * @param parent 用于QWidget初始化，并且绑定对象对象树
     */
    explicit ListTable(QWidget *parent = nullptr);
    ~ListTable();

    /**
     * @brief getTableWidget 函数功能是返回tableWidget的指针
     * @return 返回tableWidget指针
     */
    QTableWidget* getTableWidget();
    /**
     * @brief setList 函数功能是设置list
     * @param list 需要设置的list指针
     */
    void setList(CourseList* list);
    /**
     * @brief updateTable 函数功能是加载并且更新table
     */
    void updateTable();
    /**
     * @brief addRow 函数功能是增加一行, 这是一个槽函数
     */
    void addRow();
    /**
     * @brief removeRow 函数功能是删除当前行, 这是一个槽函数
     */
    void removeRow();
    /**
     * @brief getCurrentList 获取当前链表
     * @return 归还当前table内数据的链表
     */
    CourseList* getCurrentList();
    /**
     * @brief setSortm  设置排序顺序
     * @param sort 枚举变量，定义排序顺序
     */
    void setSortm(Sortm sort);
    /**
     * @brief setSearch这是一个槽函数,用于给出搜索的选项和字符串
     * @note  这里str是一个const引用，减小复制开销
     * @param item 搜索选项
     * @param str 搜索所用字符串
     */
    void setSearch(Sortm item, const QString& str);
    /**
     * @brief getSortm 函数功能是获取现在的排序状况
     * @note  这是一个内联函数
     * @return 现在的排序状况
     */
    Sortm getSortm() { return this->sort_; }
protected:
    /**
     * @brief resizeEvent 是一个重载函数
     * @param e
     */
    virtual void resizeEvent(QResizeEvent* e) override;

private:
    Ui::ListTable *ui;
    const QList<double> columnpro = {0.12, 0.12, 0.12, 0.12, 0.15, 0.15, 0.15, 0.07}; ///< 每一个表头的比例
    CourseList* list_; ///< 节点链表
    QStringList headList_; ///< 表头
    Sortm sort_; ///< 排序枚举
    bool status_; ///< 保存状态

    /**
     * @brief ListTable 拷贝构造函数，防止拷贝构造
     */
    ListTable(ListTable&){}

signals:
};

#endif // LISTTABLE_H
