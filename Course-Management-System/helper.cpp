#include "helper.h"
#include "ui_helper.h"

Helper::Helper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Helper)
{
    ui->setupUi(this);

    // 防止内存泄漏
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    // 窗口标题
    this->setWindowTitle("帮助");
    // 设置窗口固定大小
    this->setFixedSize(this->width(), this->height());
}

Helper::~Helper()
{
    delete ui;
}
