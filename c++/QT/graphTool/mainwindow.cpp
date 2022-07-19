#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      setting(new QSettings(QSettings::NativeFormat, QSettings::UserScope, "graphTool")),
      scene(setting)
{
    // 初始化
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->teDataGet->setPlaceholderText("请按格式输入 :出点 入点 权值\n图中的点是可以选中，或者是移动的");

    setWindowTitle("GraphicsTool");

    // 如果setting里面没有mode
    initSetting();


    // 第一次初始化模式
    mode = sceneMode(setting->value("mode").toInt());
    if (mode == matrix)
    {
        allowMatrix();
        setMouseTracking(false);
    }
    else if (mode == click)
    {
        canntMatrix();
        setMouseTracking(true);
    }

    // 设置背景颜色
    scene.setBackgroundBrush(setting->value("BackgroundColor").value<QColor>());

    // 信号与槽
    connect(ui->pbGetValue, &QPushButton::clicked, this, &MainWindow::getValue);
    connect(ui->actionSet, &QAction::triggered, this, &MainWindow::openSettingWidget);
    connect(ui->actionSaveFile, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSavePicture, &QAction::triggered, this, &MainWindow::savePicture);
    connect(ui->pbClear, &QPushButton::clicked, this, &MainWindow::clearAll);
    connect(ui->actionOpenFile, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionteach, &QAction::triggered, this, &MainWindow::openHelpWidget);

    // 作者
    connect(ui->actionauthor, &QAction::triggered, this, [=]{
        AuthorWidget* aw = new AuthorWidget();
        aw->show();
    });
//    // 帮助
//    connect()
    // coffee
    connect(ui->actioncoffee, &QAction::triggered, this, [=]{
        CoffeeWidget* cw = new CoffeeWidget();
        cw->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete setting;
}

void MainWindow::getValue()
{
    // 获取文本
    QString text = ui->teDataGet->toPlainText();
    QStringList lineText = text.split("\n");

    // 判断文本是否为空
    if (lineText.size() >= 1)
        for (auto item : lineText)
        {
            auto listData = item.split(" ");

            if (listData[0] == "")
                continue;

            if (listData.size() != 3)
            {
                QMessageBox::warning(this, "数据发生错误", "你的数据格式有问题");
                break;
            }

            //获取值
            int u = listData[0].toInt();
            int v = listData[1].toInt();
            int w = listData[2].toInt();

            scene.addEdge(u, v, w);
        }
    else
        QMessageBox::warning(this, "数据发生错误", "你的数据是空的");
}

void MainWindow::openSettingWidget()
{
    // 打开设置窗口
    SettingWidget* sw = new SettingWidget(setting);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    sw->show();

    connect(sw, &SettingWidget::updateSetting, this, &MainWindow::clearAll);
    connect(sw, &SettingWidget::canntMatrix, this, &MainWindow::canntMatrix);
    connect(sw, &SettingWidget::allowMatrix, this, &MainWindow::allowMatrix);
}

void MainWindow::clearAll()
{
    scene.clearAll();
    ui->graphicsView->update();
}

void MainWindow::savePicture()
{
    QImage image(ui->graphicsView->size().width(), ui->graphicsView->height(), QImage::Format_RGB888);
    QPainter p(&image);
    ui->graphicsView->render(&p);
    // 获取文件路径
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "untitled.png",
                               tr("Images (*.png *.xpm *.jpg)"));

    if (!fileName.isEmpty())
    {
        image.save(fileName);
    }
}

void MainWindow::initSetting()
{
    QColor bckC = Qt::white;
    QColor nodec = Qt::white;
    QColor linec= Qt::black;
    if (setting->value("BackgroundColor").isNull()) setting->setValue("BackgroundColor", bckC);
    if (setting->value("mode").isNull())	setting->setValue("mode", matrix);
    if (setting->value("NodeSize").isNull()) setting->setValue("NodeSize", 25);
    // 默认RGB
    if (setting->value("NodeColor").isNull()) setting->setValue("NodeColor", nodec);
    // 线的默认RGB
    if (setting->value("LineColor").isNull()) setting->setValue("LineColor", linec);
    if (setting->value("LineWidth").isNull()) setting->setValue("LineWidth", 1);
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "untitled.txt",
                               tr("txt (*.txt)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);

        QString text = ui->teDataGet->toPlainText();
        file.write(text.toStdString().c_str(), text.size());
        file.close();
    }
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                               "",
                               tr("txt (*.txt)"));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QString text = file.readAll();
        ui->teDataGet->setText(text);
        file.close();
    }
}

void MainWindow::allowMatrix()
{
    ui->teDataGet->setEnabled(true);
    ui->pbGetValue->setEnabled(true);

    // 关闭鼠标追踪
    ui->graphicsView->setMouseTracking(false);
    scene.setMode(matrix);
}

void MainWindow::canntMatrix()
{
    ui->teDataGet->setEnabled(false);
    ui->pbGetValue->setEnabled(false);

    // 开启鼠标追踪
    ui->graphicsView->setMouseTracking(true);
    scene.setMode(click);
}

void MainWindow::openHelpWidget()
{
    HelperWidget* hw = new HelperWidget();
    hw->show();
}
