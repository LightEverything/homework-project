#include "sortwidget.h"
#include "ui_sortwidget.h"

SortWidget::SortWidget(Sortm now, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SortWidget),
    now(now)
{
    ui->setupUi(this);
    // 防止内存泄漏
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    // 窗口标题
    this->setWindowTitle("选择排序");
    // 设置窗口固定大小
    this->setFixedSize(this->width(), this->height());
    // 初始化已经选中的按钮
    switch(now)
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

    //
    connect(ui->pb_yes_, &QPushButton::clicked, this, [=]()
    {
        if (ui->rb_course_name_->isChecked())
            emit sortSignal(course_name);
        else if (ui->rb_course_number_->isChecked())
            emit sortSignal(course_number);
        else if (ui->rb_course_status_->isChecked())
            emit sortSignal(course_status);
        else if (ui->rb_for_major_->isChecked())
            emit sortSignal(for_major);
        else if (ui->rb_need_major_->isChecked())
            emit sortSignal(need_major);
        else if (ui->rb_manage_->isChecked())
            emit sortSignal(management);
        else if (ui->rb_teacher_->isChecked())
            emit sortSignal(teacher_name);
        else if (ui->rb_study_time_->isChecked())
            emit sortSignal(study_time);

        this->close();
    });

    connect(ui->pb_no_, &QPushButton::clicked, this, [=]()
    {
        this->close();
    });
}

SortWidget::~SortWidget()
{
    delete ui;
}
