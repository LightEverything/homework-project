#include "listtable.h"
#include "ui_listtable.h"

ListTable::ListTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListTable),
    sort_(course_name),
    status_(false)
{
    ui->setupUi(this);
    // 初始化headList_
    headList_ <<"课程名称" << "课程编码" << "学时与学分" <<
                "适用专业" << "课程性质与属性" << "先修课程" << "课程管理单位" << "课程负责人";
    // 自适应大小
    ui->tableWidget_->horizontalHeader()->setStretchLastSection(true);
}

ListTable::~ListTable()
{
    delete ui;
}

// 函数功能是返回tableWidget的指针
QTableWidget* ListTable::getTableWidget()
{
    return ui->tableWidget_;
}

// 函数功能是加载table
void ListTable::updateTable()
{
    // 还原所有隐藏行
    if (status_)
    {
        for (int i = 0; i < ui->tableWidget_->rowCount(); i++)
        {
            if (ui->tableWidget_->isRowHidden(i))
                ui->tableWidget_->showRow(i);
        }
        status_ = false;
    }
    // 设置tablewidget的初始化参数
    ui->tableWidget_->setColumnCount(8);
    ui->tableWidget_->setRowCount(list_->size);
    ui->tableWidget_->setHorizontalHeaderLabels(headList_);

    if (list_->size != 0)
    {
        auto p = list_->head->next;
        int row = 0;
        // 用list链表的数据初始化表格
        for (; p != NULL; p = p->next, row++)
        {
            // 初始化表格
            int colmn = 0;
            QTableWidgetItem* item_study_score = new QTableWidgetItem(p->course_name);
            ui->tableWidget_->setItem(row, colmn++, item_study_score);
            QTableWidgetItem* item_course_number = new QTableWidgetItem(p->course_number);
            ui->tableWidget_->setItem(row, colmn++, item_course_number);
            QTableWidgetItem* item_study_time = new QTableWidgetItem(p->study_time);
            ui->tableWidget_->setItem(row, colmn++, item_study_time);
            QTableWidgetItem* item_set_major = new QTableWidgetItem(p->need_major);
            ui->tableWidget_->setItem(row, colmn++, item_set_major);
            QTableWidgetItem* item_course_status = new QTableWidgetItem(p->course_status);
            ui->tableWidget_->setItem(row, colmn++, item_course_status);
            QTableWidgetItem* item_need_major = new QTableWidgetItem(p->for_major);
            ui->tableWidget_->setItem(row, colmn++, item_need_major);
            QTableWidgetItem* item_managment = new QTableWidgetItem(p->management);
            ui->tableWidget_->setItem(row, colmn++, item_managment);
            QTableWidgetItem* item_teacher_name = new QTableWidgetItem(p->teacher_name);
            ui->tableWidget_->setItem(row, colmn++, item_teacher_name);
        }
    }
    // 设置排序
    ui->tableWidget_->sortItems(sort_);
    ui->tableWidget_->update();


    return ;
}

// 函数功能是增加一行,返回值为true时表示成功添加
void ListTable::addRow()
{
    int row_num = ui->tableWidget_->currentRow();
    ui->tableWidget_->insertRow(row_num + 1);
    // 对每一列的数据进行遍历
    for (int i = 0; i < 8; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("");
        ui->tableWidget_->setItem(row_num + 1, i, item);
    }
    return ;
}

// 函数功能是删除当前行,返回值为true时表示成功删除
void ListTable::removeRow()
{
    int row_num = ui->tableWidget_->currentRow();
    return ui->tableWidget_->removeRow(row_num);
}

// 创建一个基于现在状态的List, 将其返回,注意：此re必须被释放
CourseList* ListTable::getCurrentList()
{
    CourseList* re = new CourseList();
    ::createList(re);
    for (int i = 0; i < ui->tableWidget_->rowCount(); i++)
            addNode(re, ui->tableWidget_->item(i, 0)->text().toStdString().c_str(),
                    ui->tableWidget_->item(i, 1)->text().toStdString().c_str(),
                    ui->tableWidget_->item(i, 2)->text().toStdString().c_str(),
                    ui->tableWidget_->item(i, 3)->text().toStdString().c_str(),
                    ui->tableWidget_->item(i, 4)->text().toStdString().c_str(),
                    ui->tableWidget_->item(i, 5)->text().toStdString().c_str(),
                    ui->tableWidget_->item(i, 6)->text().toStdString().c_str(),
                    ui->tableWidget_->item(i, 7)->text().toStdString().c_str());
    return re;
}

// 函数功能是设置list
void ListTable::setList(CourseList* list)
{
    this->list_ = list;
    return ;
}

// 设置排序顺序,并且更新
void ListTable::setSortm(Sortm sort_)
{
    this->sort_ = sort_;
    this->updateTable();
}

// 这是一个槽函数，第一个变量是item，第二个是搜索的str
void ListTable::setSearch(Sortm item, const QString& str)
{
    // 遍历并且寻找对应数据
    for (int i = 0; i < ui->tableWidget_->rowCount(); i++)
    {
        auto tw_item = ui->tableWidget_->item(i, item);
        if (!tw_item->text().contains(str))
            ui->tableWidget_->hideRow(i);
    }
    status_ = true;
    return ;
}

void ListTable::resizeEvent(QResizeEvent* e)
{
    double now_width = 0;
    for (int i = 0; i < 8; i++)
        now_width += ui->tableWidget_->columnWidth(i);

    for (int i = 0; i < 8; i++)
        ui->tableWidget_->setColumnWidth(i, now_width * columnpro[i]);

    return QWidget::resizeEvent(e);
}
