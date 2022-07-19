#include "coursenode.h"

// 参数list是需要创建的链表指针，函数功能是创建一个链表
void createList(CourseList* list)
{
    // 初始化head指针
    list->head = (CourseNode*)malloc(sizeof(CourseNode));
    list->head->next = NULL;
    list->size = 0;
    // 尾指针指向空头指针
    list->tail = list->head;
    return ;
}

// 参数node是需要删除的节点，函数功能是删除一个节点
void deleteANode(CourseList* list, CourseNode* node)
{
    // 具体化当node为tail时
    if (node == list->tail)
    {
        CourseNode* pre = list->head;
        while (pre->next != NULL && pre->next->next != NULL)
            pre = pre->next;
        if (pre == list->head)
            return ;
        else
        {
           list->tail = pre;
           // 这里不用担心内存泄漏
           list->tail->next = NULL;
        }
    }

    free(node);
    list->size--;
    return ;
}

// 参数list是链表指针，接下来参数是数据，函数功能是创建一个节点
void addNode(CourseList* list, const char* course_name, const char* course_number,
             const char* study_time, const char* for_major, const char* course_status,
             const char* need_major, const char* management, const char* teacher_name)
{
    // 初始化并且创建tmp
    CourseNode* tmp =  (CourseNode*)malloc(sizeof(CourseNode));
    tmp->next = NULL;
    strcpy(tmp->study_time, study_time);
    strcpy(tmp->course_name, course_name);
    strcpy(tmp->course_status, course_status);
    strcpy(tmp->teacher_name, teacher_name);
    strcpy(tmp->management, management);
    strcpy(tmp->course_number, course_number);
    strcpy(tmp->need_major, need_major);
    strcpy(tmp->for_major, for_major);

    // 链表更改
    list->tail->next = tmp;
    list->tail = tmp;
    list->size ++;
    return ;
}

// 参数list是链表，函数功能是释放内存
void deleteList(CourseList* list)
{
    for (CourseNode* p = list->head; p != NULL;)
    {
        CourseNode* pre = p->next;
        deleteANode(list, p);
        p = pre;
    }
}

// 参数list是链表，oldnode是原来的节点指针，newnode是需要修改成的指针
void updateNode(CourseList* list, CourseNode* oldnode, CourseNode* newnode)
{
    strcpy(oldnode->study_time, newnode->study_time);
    strcpy(oldnode->course_name, newnode->course_name);
    strcpy(oldnode->course_status, newnode->course_status);
    strcpy(oldnode->teacher_name, newnode->teacher_name);
    strcpy(oldnode->management, newnode->management);
    strcpy(oldnode->course_number, newnode->course_number);
    strcpy(oldnode->need_major, newnode->need_major);
    strcpy(oldnode->for_major, newnode->for_major);
}

// 参数a，b分别是比较的指针，函数功能是根据课程码来比较两节课是否相同, 相同返回1
int  cmpNode(CourseNode* a, CourseNode* b)
{
    if (!strcmp(a->course_number, b->course_number))
        return 1;

    return 0;
}

// 参数list是链表，course_number是课程代码，如果存在则返回指针，不存在则返回NULL
CourseNode* findNode(CourseList* list, const char* course_number)
{
    for (CourseNode* p = list->head; p != NULL;)
    {
        if (!strcmp(p->course_number, course_number))
            return p;
        p = p->next;
    }

    return NULL;
}
