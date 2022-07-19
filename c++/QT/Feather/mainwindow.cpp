#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QFontDialog>
#include <QByteArray>
#include <QFileDialog>
#include <QTextStream>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeData()
{
    // 打开文件
    QFile* file = this->openWrite();

    // 判断错误
    if (!file)  return ;

    //写入文件
    QTextStream data(file);
    QByteArray dataArray;
    QTextEdit* tempw=dynamic_cast<QTextEdit*>(ui->tabWidget_tabtext->currentWidget());

    // 数据存到dataArray
    dataArray += tempw->toPlainText();
    data << dataArray;
    file->close();

    return ;
}

void MainWindow::setNewTab()
{

    // 一个新的文本框
    TextInput* tempTextInput = new TextInput();
    tempTextInput->setSetFile(QFileDialog::getOpenFileName());
    QFile* file = tempTextInput->getSetFile();

    // 是否成功写入
    if (file == nullptr)
           return ;
    else
        file->open(QIODevice::ReadOnly);

    QFileInfo fileInfo(*file);
    QTextStream data(file);
    QString tempstr;
    tempstr  = data.readAll(); // 获取文件内容
    QByteArray  dataArray;
    dataArray += tempstr;   // 存到数组里

    this->setTextWidget(tempTextInput);
    ui->tabWidget_tabtext->addTab(tempTextInput, fileInfo.fileName());
    ui->tabWidget_tabtext->setCurrentIndex(ui->tabWidget_tabtext->currentIndex() + 1);

    tempTextInput->setText(dataArray);
    file->close();

    return ;
}

void MainWindow::setTextWidget(TextInput* textedit)
{
    textedit->setFont(gbalSet.font);
}

void MainWindow::setFont()
{
    bool ok;
    this->gbalSet.font = QFontDialog::getFont(&ok, this);
    for (int i = 0; i < ui->tabWidget_tabtext->count(); i++)
        ui->tabWidget_tabtext->widget(ui->tabWidget_tabtext->currentIndex())->setFont(
                    this->gbalSet.font);

}

void MainWindow::init()
{

    // 变量设置
    QFont temp;
    temp.setPixelSize(17);
    this->gbalSet.font = temp;

    // 设置tab属性
    this->setWindowTitle("Feather");
    ui->tabWidget_tabtext->setMovable(true);
    ui->tabWidget_tabtext->setTabsClosable(true);
    ui->tabWidget_tabtext->clear();

    // 槽连接
    connect(ui->Qaction_save, &QAction::triggered, this, &MainWindow::writeData);
    connect(ui->Qaction_open, &QAction::triggered, this, &MainWindow::setNewTab);
    connect(ui->Qaction_font, &QAction::triggered, this, &MainWindow::setFont);
    connect(ui->tabWidget_tabtext, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
}

QFile* MainWindow::openWrite()
{
    if (ui->tabWidget_tabtext->count() == 0)
    {
        // 判断是否有路径
        if(!this->gbalSet.file.open(QIODevice::WriteOnly))
        {
            QString tempstr = QFileDialog::getSaveFileName();
            if (tempstr != "")
            {

                // 如果输入正确则打开文件
               this->gbalSet.file.setFileName(tempstr);
                gbalSet.file.open(QIODevice::WriteOnly);
                return &gbalSet.file;
            }
            else
                return nullptr;
        }
        else
        {
            return &gbalSet.file;
        }
    }
    else
    {
        TextInput* temptext = dynamic_cast<TextInput*>(ui->tabWidget_tabtext->widget(ui->tabWidget_tabtext
                                                                                    ->currentIndex()));
        QFile* file = temptext->getSetFile();
        file->open(QIODevice::WriteOnly);
        return file;
    }
}

void MainWindow::closeTab()
{
    ui->tabWidget_tabtext->removeTab(ui->tabWidget_tabtext
                                     ->currentIndex());
    return ;
}
