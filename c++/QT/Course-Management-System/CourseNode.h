/******************************************************************************
 * Copyright 2015-2022 wanxin xiangtan university .
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       coursenode.h
 * @brief      课程设计系统的核心部分，这个模块是纯c语言写的，其功能是建立一个链表并且存储相关信息
 *
 *
 * @author     wanxin<3234995498@qq.com>
 * @date       2022/05/20
 * @history
 *****************************************************************************/
#ifndef COURSENODE_H
#define COURSENODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QDebug>

/**
 * @brief CourseNode 是一个结构体，用来储存给出信息
 */

struct CourseNode
{
    char      study_time[255]; ///< 储存学时
    char      course_name[255]; ///< 储存课程名字
    char      course_status[255]; ///< 课程描述
    char      teacher_name[50]; ///< 老师名字
    char      management[50]; ///< 管理单位
    char      course_number[255]; ///< 课程编号

    char      need_major[1024]; ///< 需要的先修课程
    char      for_major[1024]; ///< 适用的专业
    struct CourseNode* next; ///< 指向下一个的指针
};

typedef struct CourseNode CourseNode;

/**
 * @brief CourseList 是一个结构体，是对链表的抽象\n
 * CourseNode 这个结构体储存了题目要求的信息，和链表的下一个节点。
 * CourseList 是对CourseNode的一个抽象，里面存储的是链表的头和尾部指针(由于这个程序要涉及到大量的尾部添加操作，我这里抽象了链表并且储存了尾部指针，来加快添加操作,size也是为了快速获取List)
 */

struct CourseList
{
    int size; ///< 链表大小

    CourseNode* head; ///< 头指针
    CourseNode* tail; ///< 尾指针
};

typedef struct CourseList CourseList;


/**
 * @brief createList 函数功能是创建一个链表
 * @param list 是需要创建的链表指针
 */
void createList(CourseList* list);

/**
 * @brief deleteANode 函数功能是删除一个节点
 * @param list 是传入的链表
 * @param node 是需要删除的节点
 */
void deleteANode(CourseList* list, CourseNode* node);

// 参数list，接下来参数是数据，
/**
 * @brief addNode 函数功能是创建一个节点
 * @param list 是链表指针
 * @param course_name 课程名字
 * @param course_number 课程编号
 * @param study_time 学时
 * @param for_major	哪些专业需要上
 * @param course_status 课程性质和属性
 * @param need_major 需要的先修课程
 * @param management 管理单位
 * @param teachername 老师名字
 */
void addNode(CourseList* list, const char* course_name, const char* course_number,
             const char* study_time, const char* for_major, const char* course_status,
             const char* need_major, const char* management, const char* teachername);

/**
 * @brief deleteList 函数功能是释放内存
 * @param list是链表
 */
void deleteList(CourseList* list);

/**
 * @brief updateNode 函数功能是修改链表
 * @param list是链表
 * @param oldnode是原来的节点指针
 * @param newnode是需要修改成的指针
 */
void updateNode(CourseList* list, CourseNode* oldnode, CourseNode* newnode);

/**
 * @brief cmpNode 函数功能是根据课程码来比较两节课是否相同
 * @param a表示一个节点a
 * @param b表示一个节点b
 * @return 返回是否相同
 *  -- 1 表示节点相同
 *  -- 0 表示节点不同
 */
int  cmpNode(CourseNode* a, CourseNode* b);

// 参数list是链表，course_number是课程代码，如果存在则返回指针，不存在则返回NULL
/**
 * @brief findNode 在给定链表中寻找一个节点
 * @note 这个函数是根据节点的课程编号是否相同，如果在链表中有几个相同编号的不同节点，不建议使用这个函数
 * @param list 使用的链表指针
 * @param course_number 是课程的编号
 * @return 寻找的CourseNode指针
 */
CourseNode* findNode(CourseList* list, const char* course_number);

#endif // COURSENODE_H
