/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       sortm.h
 * @brief      Sortm枚举体
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/21
 * @history
 *****************************************************************************/
#ifndef SORTM_H
#define SORTM_H

/**
 * @brief The Sortm enum 这是一个枚举，意义是枚举CourseNode的每一个变量
 */
enum Sortm
{
    course_name = 0, ///< 课程名字
    course_number, ///< 课程序号
    study_time, ///< 学时与学分
    for_major, ///< 需要上课的专业
    course_status, ///< 课程性质
    need_major, ///< 需要的先修专业·
    management, ///< 管理单位
    teacher_name ///< 老师的名字
};

typedef enum Sortm  Sortm;

#endif // SORTM_H
