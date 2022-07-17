#include "netwidget.h"
#include "ui_netwidget.h"

NetWidget::NetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetWidget),
    // 绑定对象树
    tcp_socket_(new QTcpSocket(this))
{
    ui->setupUi(this);

    // 防止内存泄漏
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    // 窗口标题
    this->setWindowTitle("选择网络链接");
    // 设置窗口固定大小
    this->setFixedSize(this->width(), this->height());

    // 链接按钮UP
    connect(ui->pb_up_, &QPushButton::clicked, [=]()
    {
        if (getWidgetData())
        {
            tcp_socket_->write("up");
            timer_up_.start(20);
            now_ = up;
        }
    });

    // 链接按钮down
    connect(ui->pb_down_, &QPushButton::clicked, [=]()
    {
        if (getWidgetData())
        {
            tcp_socket_->write("down");
            timer_down_.start(20);
            now_ = down;
        }
    });
    
    connect(&timer_up_, &QTimer::timeout, this, &NetWidget::upFile);

    connect(&timer_down_, &QTimer::timeout, [=]()
    {
        // 防止粘包
        tcp_socket_->write(file_name_.toStdString().c_str());
        timer_down_.stop();
    });
    
    connect(tcp_socket_, &QTcpSocket::readyRead, [=]()
    {
        auto data = tcp_socket_->readAll();
        QString data_str = data_str.fromLocal8Bit(data);

        switch(now_)
        {
        case down:
            downFile(data_str, data);
            break;
        case up:
            // 传输处理
            break;
        case normal:
            // 传输处理
            break;
        }
    });

}

NetWidget::~NetWidget()
{
    delete ui;
}

void NetWidget::upFile()
{
    QFileInfo file_info(file_name_);
    if (ishead_)
    {
        // 如果文件不存在
        if (!file_info.exists())
        {
            QMessageBox::warning(nullptr, "错误", "文件不存在");
            timer_up_.stop();
            tcp_socket_->write("error");
            tcp_socket_->disconnectFromHost();
            tcp_socket_->close();
            now_ = normal;
            this->close();
        }
        else
        {
            QString file_head = QString("%1##%2").arg(file_info.fileName()).arg(file_info.size());
            file_size_ = file_info.size();
            file_.setFileName(file_name_);
            // 写入文件头
            tcp_socket_->write(file_head.toStdString().c_str());
            ishead_= false;
        }

    }
    else
    {
        file_.open(QIODevice::ReadOnly);
        auto data = file_.readAll();
        int file_size = tcp_socket_->write(data);
        // 判断文件是否传输成功
        if (file_size == file_size_)
            QMessageBox::warning(this, "成功", "传输成功");
        else
            QMessageBox::warning(this, "错误", "传输失败");

        timer_up_.stop();
        tcp_socket_->disconnectFromHost();
        tcp_socket_->close();
        now_ = normal;
        this->close();
    }
}

void NetWidget::downFile(const QString& data_str, const QByteArray& data)
{
    if (ishead_)
    {
        if (data_str == "error")
        {
            tcp_socket_->close();
            now_ = normal;
            this->close();
        }
        else
        {
            auto file_name= data_str.section("##", 0, 0);
            this->file_size_ = data_str.section("##", 1, 1).toInt();
            file_.setFileName(file_name);
            ishead_ = false;
        }
    }
    else
    {

        int  write_len = 0;

        if (!file_.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(this, "标题", "打开文件失败");
            tcp_socket_->disconnectFromHost();
            tcp_socket_->close();
            now_ = normal;
            this->close();
        }
        else
        {
            write_len = file_.write(data);
            // 传输状态之后关闭
            if (write_len == file_size_)
                QMessageBox::warning(this, "成功", "文件传输成功");
            else
                QMessageBox::warning(this, "成功", "文件传输失败");

            tcp_socket_->disconnectFromHost();
            tcp_socket_->close();
            file_.close();
            this->close();
        }
        ishead_ = true;
    }
}

bool NetWidget::getWidgetData()
{
    QString ip = ui->le_address_->text();
    auto port = ui->le_port_->text().toInt();
    file_name_ = ui->le_filename_->text();

    tcp_socket_->connectToHost(QHostAddress(ip), port);
    return true;
}
