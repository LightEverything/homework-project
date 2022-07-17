#include "charttable.h"
#include "ui_charttable.h"

ChartTable::ChartTable(CourseList* list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartTable),
    list(list)
{
    ui->setupUi(this);
    // 防止内存泄漏,此函数功能是关闭窗口时自动释放
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    // 窗口标题
    this->setWindowTitle("信息统计");
    ui->tabWidget_->setTabText(0, "课程属性与性质");
    ui->tabWidget_->setTabText(1, "老师名字");
    // 设置课程性质
    this->setCourseStatusTable();
    // 设置老师名字
    this->setTeacherNameTable();
}

// 这里大部分资源对象树已经释放
ChartTable::~ChartTable()
{
    delete ui;
}

// 函数功能是设置课程性质
void ChartTable::setCourseStatusTable()
{
    std::map<QString, int> name_and_sum;

    for (auto p = list->head->next; p != NULL; p = p->next)
    {
        name_and_sum[p->course_status] ++;
    }

    // 根据qt的对象树，这里已经释放
    QChart* m_chart = new QChart();
    QPieSeries* series = new QPieSeries();

    for (auto item : name_and_sum)
    {
        QString tmp = QString("%1:%2").arg(item.first).arg(item.second);
        series->append(tmp, qreal(item.second));
    }

    series->setLabelsVisible(true);
    // 设置立体效果，打开opengl
    series->setUseOpenGL(true);

    m_chart->setTheme(QChart::ChartThemeLight);
    m_chart->setDropShadowEnabled(true);
    m_chart->addSeries(series);

    m_chart->setTitleBrush(QBrush(QColor(0, 0, 255)));
    m_chart->setTitleFont(QFont("微软雅黑"));
    m_chart->setTitle("课程选修情况");

    //修改说明样式
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignRight);
    m_chart->legend()->setBackgroundVisible(true);
    m_chart->legend()->setAutoFillBackground(true);
    m_chart->legend()->setColor(QColor(222, 233, 251));
    m_chart->legend()->setLabelColor(QColor(0, 100, 255));
    ui->cv_course_status_->setChart(m_chart);
}

// 函数功能是设置老师名字
void ChartTable::setTeacherNameTable()
{
    std::map<QString, int> name_and_sum;

    for (auto p = list->head->next; p != NULL; p = p->next)
    {
        // 将两个老师名字组合的拆分
        QStringList tmp = QString(p->teacher_name).split("、");

        for (auto pstr : tmp)
            name_and_sum[pstr]++;
    }

//    qDebug() << name_and_sum;
    // 根据qt的对象树，这里已经释放
    QChart* m_chart = new QChart();
    QPieSeries* series = new QPieSeries();

    for (auto item : name_and_sum)
    {
        QString tmp = QString("%1:%2").arg(item.first).arg(item.second);
        series->append(tmp, qreal(item.second));
    }

    series->setLabelsVisible(true);
    // 设置立体效果，打开opengl
    series->setUseOpenGL(true);

    m_chart->setTheme(QChart::ChartThemeLight);
    m_chart->setDropShadowEnabled(true);
    m_chart->addSeries(series);

    m_chart->setTitleBrush(QBrush(QColor(0, 0, 255)));
    m_chart->setTitleFont(QFont("微软雅黑"));
    m_chart->setTitle("课程负责人");

    //修改说明样式
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignRight);
    m_chart->legend()->setBackgroundVisible(true);
    m_chart->legend()->setAutoFillBackground(true);
    m_chart->legend()->setColor(QColor(222, 233, 251));
    m_chart->legend()->setLabelColor(QColor(0, 100, 255));
    ui->cv_teacher_name_->setChart(m_chart);
}
