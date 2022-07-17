/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       netwidget.h
 * @brief      tcp网络控制界面类，用来可视化操作文件的云备份
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/21
 * @history
 *****************************************************************************/

#ifndef NETWIDGET_H
#define NETWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QHostAddress>
#include <QTimer>

#include "ConnectStatus.h"

namespace Ui {
class NetWidget;
}

/**
 * @brief The NetWidget class 用于可视化操作网络的界面类
 * @note 通信协议是tcp协议
 */
class NetWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief NetWidget的构造函数
     * @param parent 用于QWidget初始化，并且绑定对象对象树
     */
    explicit NetWidget(QWidget *parent = nullptr);
    ~NetWidget();

private:
    Ui::NetWidget *ui;

    int 	file_size_; ///< 文件大小
    bool    ishead_ = true; ///< 是否是头数据
    QTcpSocket* tcp_socket_; ///< tcp套接字
    QFile 	file_; ///< 文件
    QString file_name_; ///< 文件名
    QTimer  timer_up_; ///< 防止粘包计时器Up
    QTimer 	timer_down_; ///< 防止粘包计时器Down
    ConnectStatus now_ = normal; ///< 存在模式

    /**
     * @brief upFile 函数功能上传文件
     */
    void upFile();
    /**
     * @brief downFile 函数功能更新本地文件
     * @param data_str 数据头（部分数据字符串）
     * @param data 以二进制存储的数据引用
     */
    void downFile(const QString& data_str, const QByteArray& data);
    /**
     * @brief getWidgetData 函数功能获取控件信息
     * @return 返回值表示是否成功获取
     * -- true 成功获取
     * -- false 获取失败
     */
    bool getWidgetData();
};

#endif // NETWIDGET_H
