#include "helperwidget.h"
#include "ui_helperwidget.h"

HelperWidget::HelperWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelperWidget)
{
    ui->setupUi(this);
    ui->label->setOpenExternalLinks(true);
    QString url = "<a style='color: red; text-decoration: none; font-size: 20px;' "
                  "href = http://120.27.213.171/2022/04/23/graphTool%E4%BD%BF%E7%94%A8%E6%96%87%E6%A1%A3> > 教程戳这里";
    ui->label->setText(url);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

HelperWidget::~HelperWidget()
{
    delete ui;
}
