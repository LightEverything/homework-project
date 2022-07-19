#ifndef COFFEEWIDGET_H
#define COFFEEWIDGET_H

#include <QDialog>

namespace Ui {
class CoffeeWidget;
}

class CoffeeWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CoffeeWidget(QWidget *parent = nullptr);
    ~CoffeeWidget();

private:
    Ui::CoffeeWidget *ui;
};

#endif // COFFEEWIDGET_H
