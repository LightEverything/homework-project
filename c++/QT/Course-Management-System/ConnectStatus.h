#ifndef CONNECTSTATUS_H
#define CONNECTSTATUS_H

/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       ConnectStatus.h
 * @brief      链接状态的枚举体
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/20
 * @history
 *****************************************************************************/

/**
 * @brief ConnectStatus 这是一个枚举，表示链接的状态
 */
enum ConnectStatus
{
    up, ///< 上传
    down, ///< 下载
    normal ///< 监听
};

typedef enum ConnectStatus ConnectStatus;


#endif // CONNECTSTATUS_H
