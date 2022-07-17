#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QColorDialog>
#include <QScrollArea>
#include <QSettings>
#include <QLabel>
#include <QButtonGroup>
#include "nodegraphscene.h"

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QSettings* setting, QWidget *parent = nullptr);
    ~SettingWidget();

private:
    int 			   usPixSize;
    int 			   usLineWidth;
    int 			   usPixdis;
    Ui::SettingWidget* ui;
    QSettings* 		   setting;
    QColor             usPixColor;
    QColor 			   usLineColor;
    sceneMode 		   usmode;

    void initWidget();
    void connectWidget();
    void saveSetting();

signals:
    void updateSetting();
    void canntMatrix();
    void allowMatrix();
};

#endif // SETTINGWIDGET_H
