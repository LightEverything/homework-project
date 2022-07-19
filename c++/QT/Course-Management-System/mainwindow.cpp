#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      list_(new CourseList()),
      icon_(":/book.jpg"),
      new_icon_(":/new.jpg")
{
    ui->setupUi(this);

    // 创建链表
    ::createList(list_);
    this->setWindowTitle("学生课堂管理系统");
    this->setWindowIcon(icon_);
    this->setCentralWidget(ui->stackedWidget);
    this->setGeometry(50, 50, 900, 650);

    ui->stackedWidget->setCurrentWidget(ui->wg_welcome_);
    ui->toolBar->hide();

    connect(ui->pb_openfile_, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->pb_newfile_, &QPushButton::clicked, this, &MainWindow::newFile);

    connect(ui->action_save_, &QAction::triggered, this, [=]()
    {
        if (QMessageBox::Yes == QMessageBox::question(this, "是否保存", "你是否要保存文件，这是一个不可撤销操作"))
            saveFile();
    });

    connect(ui->action_reValue_, &QAction::triggered, this, [=]()
    {
        if (QMessageBox::Yes == QMessageBox::question(this, "是否撤销", "你是否要撤销回最开始，这是一个不可撤销操作"))
            revalue();
    });

    connect(ui->action_insert_, &QAction::triggered, ui->wg_table_, &ListTable::addRow);
    connect(ui->action_del_, &QAction::triggered, ui->wg_table_, &ListTable::removeRow);

    // 连接排序按钮
    connect(ui->action_sort_, &QAction::triggered, this, [=]()
    {
        // 内存在sw里面释放，这里不需要担心内存泄漏
        SortWidget* sw = new SortWidget(ui->wg_table_->getSortm());
        sw->show();
        connect(sw, &SortWidget::sortSignal, ui->wg_table_, &ListTable::setSortm);
    });
    // 连接搜索按钮
    connect(ui->action_search_, &QAction::triggered, this, [=]()
    {
        SearchWidget* sw = new SearchWidget();
        sw->show();
        connect(sw, &SearchWidget::searchItem, ui->wg_table_, &ListTable::setSearch);
    });
    // 连接表格按钮
    connect(ui->action_chart_, &QAction::triggered, this, [=]()
    {
        ChartTable* ct = new ChartTable(list_);
        ct->show();
    });

    connect(ui->action_net_, &QAction::triggered, this, [=]()
    {
        NetWidget* nw = new NetWidget();
        nw->show();
    });

    connect(ui->action_helper_, &QAction::triggered, this, [=]()
    {
        Helper* h = new Helper();
        h->show();
    });

    connect(ui->action_remain_, &QAction::triggered, this, &MainWindow::reWelcomeWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    ::deleteList(list_);
    delete list_;
}


// 函数功能是打开一个文件
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件",  "./", tr("cms (*.cms)"));
    //文件不为空
    if (!fileName.isEmpty())
    {
        file_ = fileName;
        createList(fileName);
        changeToTable();
    }
}

// 参数是string的文件名，函数功能是初始化数组
void MainWindow::createList(const QString& filename)
{

    // 打开文件
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        perror("打开文件错误");

    QTextStream ds(&file);
    ds.setCodec("UTF-8");
    while (!ds.atEnd())
    {
        // 创建变量储存
        QString  study_time, course_name, course_status, tearch_name,
             management, course_number, need_major, for_major;

        // 输入变量
        course_name = ds.readLine();
        course_number = ds.readLine();
        study_time = ds.readLine();
        need_major = ds.readLine();
        course_status = ds.readLine();
        for_major = ds.readLine();
        management = ds.readLine();
        tearch_name = ds.readLine();
        // 添加一个新节点
       ::addNode(list_, course_name.toStdString().c_str() , course_number.toStdString().c_str(),
                 study_time.toStdString().c_str(),
                 need_major.toStdString().c_str(),
                 course_status.toStdString().c_str(),
                 for_major.toStdString().c_str(),
                 management.toStdString().c_str(),
                 tearch_name.toStdString().data());
    }
    // 删除多余一行
    file.close();
}

// 函数功能是切换到Table页面
void MainWindow::changeToTable()
{
    ui->toolBar->show();
    ui->stackedWidget->setCurrentWidget(ui->wg_table_);
    ui->wg_table_->setList(list_);
    ui->wg_table_->updateTable();
}

// 函数功能是将表格保存到文件
void MainWindow::saveFile()
{
    // 释放原来的list_内存
    ::deleteList(list_);
    delete list_;
    // 获得内存
    list_ = ui->wg_table_->getCurrentList();
    // 更新table
    ui->wg_table_->setList(list_);
    ui->wg_table_->updateTable();

    // 保存文件
    QFile file(file_);
    if (!file.open(QIODevice::WriteOnly))
        QMessageBox::warning(this, "错误", "文件无法打开");

    // 初始化barr
    auto p = list_->head->next;
    QByteArray barr;
    for (; p != NULL; p = p->next)
    {
        // 构造tmp字符串储存数据
        QString tmp = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n%8\n").arg(p->course_name).\
                                                          arg(p->course_number).\
                                                          arg(p->study_time).\
                                                          arg(p->for_major).\
                                                          arg(p->course_status).\
                                                          arg(p->need_major).\
                                                          arg(p->management).\
                                                          arg(p->teacher_name);
        barr.append(tmp);
    }

    // 写入文件
    file.write(barr);
    return file.close();
}

// 函数功能是将表格还原
void MainWindow::revalue()
{
    ui->wg_table_->setList(list_);
    ui->wg_table_->updateTable();
}

// 打开一个新文件
void MainWindow::newFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "选择文件保存位置", "./", "*.cms");

    if (!fileName.isEmpty())
    {
        file_ = fileName;
        ::createList(list_);
        changeToTable();
    }
}

void MainWindow::reWelcomeWidget()
{
    ui->toolBar->hide();
    // 清空表格
    ui->wg_table_->getTableWidget()->clear();
    ui->stackedWidget->setCurrentIndex(0);
    // 释放内存
    ::deleteList(list_);
    delete list_;
    // 新建节点
    list_ = new CourseList();
    ::createList(list_);
}
