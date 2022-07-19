#ifndef HELPERWIDGET_H
#define HELPERWIDGET_H

#include <QDialog>

namespace Ui {
class HelperWidget;
}

class HelperWidget : public QDialog
{
    Q_OBJECT

public:
    explicit HelperWidget(QWidget *parent = nullptr);
    ~HelperWidget();

private:
    void setStackWidget();
    Ui::HelperWidget *ui;
};

#endif // HELPERWIDGET_H
