#include "authorwidget.h"
#include "ui_authorwidget.h"

AuthorWidget::AuthorWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorWidget)
{
    ui->setupUi(this);
    ui->labelText->setText(
                "作者：lightEverything\n\n"
                "源码位置：https://github.com/LightEverything/graphTool\n\n"
                "有任何问题或者是新的想法可以通过邮箱联系我:\n"
                "邮箱1：3234995498@qq.com\n"
                "邮箱2：wanxinnb@outlook.com"
                );
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("作者");
}

AuthorWidget::~AuthorWidget()
{
    delete ui;
}
