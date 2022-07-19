#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // ui初始化
    ui->setupUi(this);

    // 变量初始化
    drawBoard = new DrawingBoard(this);

    pen.setColor(Qt::black);
    pen.setWidth(2);

    this->setCentralWidget(drawBoard);

    //槽链接
    connect(ui->pbErase, &QPushButton::clicked, this, &MainWindow::useErase);
    connect(ui->pbPenColor, &QPushButton::clicked, this, &MainWindow::changePenColor);
    connect(ui->pbClear,  &QPushButton::clicked, this, &MainWindow::clearDrawBoard);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::useErase()
{
    if (!drawBoard->isErase())
        drawBoard->setPenMode(DrawingBoard::eraser);
    else
        drawBoard->setPenMode(DrawingBoard::write);

    return true;
}

bool MainWindow::changePenColor()
{
    QColor tmpC = QColorDialog::getColor(Qt::black, this, "选取笔的颜色");
    pen.setColor(tmpC);
    drawBoard->setPen(pen);
    return true;
}

bool MainWindow::clearDrawBoard()
{
    drawBoard->clear();
    return true;
}
