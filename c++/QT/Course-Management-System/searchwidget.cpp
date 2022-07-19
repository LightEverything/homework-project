#include "searchwidget.h"
#include "ui_searchwidget.h"

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);
    // 防止内存泄漏
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    // 窗口标题
    this->setWindowTitle("模糊搜索");
    // 设置窗口固定大小
    this->setFixedSize(this->width(), this->height());

    // 初始化已经选中的按钮
    switch(default_option_)
    {
    case course_name:
        ui->rb_course_name_->setChecked(true);
        break;
    case course_status:
        ui->rb_course_status_->setChecked(true);
        break;
    case study_time:
        ui->rb_study_time_->setChecked(true);
        break;
    case for_major:
        ui->rb_for_major_->setChecked(true);
        break;
    case need_major:
        ui->rb_need_major_->setChecked(true);
        break;
    case management:
        ui->rb_manage_->setChecked(true);
        break;
    case teacher_name:
        ui->rb_teacher_->setChecked(true);
        break;
    case course_number:
        ui->rb_course_number_->setChecked(true);
        break;
    }

    connect(ui->pb_search_, &QPushButton::clicked, this, [=]()
    {
        QString tmp_str = ui->lineEdit->text();
        Sortm   search_item;

        // search_item赋值
        if (ui->rb_course_name_->isChecked())
            search_item = course_name;
        else if (ui->rb_course_number_->isChecked())
            search_item = (course_number);
        else if (ui->rb_course_status_->isChecked())
            search_item = (course_status);
        else if (ui->rb_for_major_->isChecked())
            search_item = (for_major);
        else if (ui->rb_need_major_->isChecked())
            search_item = (need_major);
        else if (ui->rb_manage_->isChecked())
            search_item = (management);
        else if (ui->rb_teacher_->isChecked())
            search_item = (teacher_name);
        else
            search_item =  (study_time);

        emit searchItem(search_item, tmp_str);
        this->close();
    });
}

SearchWidget::~SearchWidget()
{
    delete ui;
}
