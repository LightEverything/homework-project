#ifndef AUTHORWIDGET_H
#define AUTHORWIDGET_H

#include <QDialog>

namespace Ui {
class AuthorWidget;
}

class AuthorWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorWidget(QWidget *parent = nullptr);
    ~AuthorWidget();

private:
    Ui::AuthorWidget *ui;
};

#endif // AUTHORWIDGET_H
