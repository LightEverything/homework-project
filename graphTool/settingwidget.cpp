#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QSettings* setting, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget),
    setting(setting)
{
    initWidget();
    connectWidget();
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::initWidget()
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentWidget(0);
    // tab设置
    ui->tabWidget->setTabText(0, "点和线可视化设置");
    ui->tabWidget->setTabText(1, "点的间隔设置");
    // 设置大小
    ui->lineEdgeWidth->setText(QString().setNum(setting->value("LineWidth").toInt()));
    ui->linePixSize->setText(QString().setNum(setting->value("NodeSize").toInt()));
    // 设置颜色
    ui->labelColorLine->setAutoFillBackground(true);
    QPalette pteLine(setting->value("LineColor").value<QColor>());
    ui->labelColorLine->setPalette(pteLine);
    ui->labelColorPix->setAutoFillBackground(true);
    QPalette pteNode(setting->value("NodeColor").value<QColor>());
    ui->labelColorPix->setPalette(pteNode);
    usPixColor = setting->value("NodeColor").value<QColor>();
    usLineColor = setting->value("LineColor").value<QColor>();
    // 设置模式
    usmode = sceneMode(setting->value("mode").toInt());

    switch (usmode)
    {
    case matrix:
        ui->rbSetMatrix->setChecked(true);
        break;
    case click:
        ui->rbSetClick->setChecked(true);
        break;
    }
    // 设置标签
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setWindowTitle("设置");
}

void SettingWidget::connectWidget()
{
    connect(ui->pbCancel, &QPushButton::clicked, this, &QWidget::close);

    connect(ui->pbPixColorGet, &QPushButton::clicked, this, [=]()
    {
        if (!(this->usPixColor = QColorDialog::getColor(setting->value("NodeColor").value<QColor>())).isValid())
            this->usPixColor = setting->value("NodeColor").value<QColor>();
        else
        {
            QPalette pteLine(usPixColor);
            ui->labelColorPix->setPalette(pteLine);
        }
    });

    connect(ui->pbEdgeColorGet, &QPushButton::clicked, this, [=]()
    {
        if (!(this->usLineColor= QColorDialog::getColor(setting->value("LineColor").value<QColor>())).isValid())
            this->usLineColor = setting->value("LineColor").value<QColor>();
        else
        {
            QPalette pteLine(usLineColor);
            ui->labelColorLine->setPalette(pteLine);
        }
    });

    connect(ui->pbOK, &QPushButton::clicked, this, [=]()
    {
        usLineWidth = ui->lineEdgeWidth->text().toInt();
        usPixSize = ui->linePixSize->text().toInt();

        // 发模式信号
        if (ui->rbSetClick->isChecked())
        {
            usmode = click;
            emit canntMatrix();
        }
        else if (ui->rbSetMatrix->isChecked())
        {
            usmode = matrix;
            emit allowMatrix();
        }

        saveSetting();
        emit updateSetting();

        close();
    });
}

void SettingWidget::saveSetting()
{
    setting->setValue("LineWidth", usLineWidth);
    setting->setValue("LineColor", usLineColor);
    setting->setValue("NodeSize", usPixSize);
    setting->setValue("NodeColor", usPixColor);
    setting->setValue("mode", usmode);
}
