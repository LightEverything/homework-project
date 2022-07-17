#include "coffeewidget.h"
#include "ui_coffeewidget.h"

CoffeeWidget::CoffeeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoffeeWidget)
{
    ui->setupUi(this);
    QPixmap coffee(":/coffee.png");
    coffee.setDevicePixelRatio(5.5);
    ui->labelCoffee->setPixmap(coffee);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("支持一下作者呗~~~");
}

CoffeeWidget::~CoffeeWidget()
{
    delete ui;
}
