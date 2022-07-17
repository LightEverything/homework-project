#ifndef HELPER_H
#define HELPER_H

#include <QWidget>

namespace Ui {
class Helper;
}

class Helper : public QWidget
{
    Q_OBJECT

public:
    explicit Helper(QWidget *parent = nullptr);
    ~Helper();

private:
    Ui::Helper *ui;
};

#endif // HELPER_H
