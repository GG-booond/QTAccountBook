
#include "reportWindow.h"
#include <QGraphicsWidget>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QVBoxLayout>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
#include <QDebug>

using namespace std;

reportWindow::reportWindow(mainData* db, QWidget *parent)
    : QMainWindow(parent), database(db),pieChart(nullptr), lineChart(nullptr),
    pieChartView(new QChartView(this)),
    lineChartView(new QChartView(this))
{
    this->setWindowTitle("查看报表");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pieChartView);
    layout->addWidget(lineChartView);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    resize(800, 600);
}

void reportWindow::createPieChart() {
    QPieSeries *series = new QPieSeries();
    auto categoryExpenses = database->getCateTotalAmounts();
    QVector<QColor> colors = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkRed, Qt::darkGreen, Qt::darkBlue};

    int colorIndex = 0;
    for (auto it = categoryExpenses.begin(); it != categoryExpenses.end(); ++it) {
        QPieSlice *slice = series->append(it->first, it->second);
        slice->setLabel(it->first);  // 设置标签为类别名称
        slice->setBrush(colors[colorIndex % colors.size()]);  // 设置颜色
        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("支出用途分布");

    // 调整标题字体大小
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16);  // 设置标题字体大小
    chart->setTitleFont(titleFont);

    chart->legend()->setVisible(true);  // 显示图例
    chart->legend()->setAlignment(Qt::AlignRight);

    // 调整图例项字体大小
    QFont legendFont = chart->legend()->font();
    legendFont.setPointSize(8);  // 设置图例项字体大小
    chart->legend()->setFont(legendFont);

    pieChartView->setChart(chart);
}

void reportWindow::createLineChart() {
    QLineSeries *series = new QLineSeries();
    auto monthlyExpenses = database->getMonthlyExpenses();

    // 创建临时存储用于存放月份和对应的数值
    QMap<double, QString> monthLabels;

    int month = 1;
    for (auto it = monthlyExpenses.begin(); it != monthlyExpenses.end(); ++it, ++month) {
        QString s = it->first;
        series->append(month, it->second);
        int x = (s[6].toLatin1() == '-') ? 6 : 7;
        monthLabels[month] = s.left(x);  // 存储月份和对应的标签
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("月度支出变化趋势");

    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->setTitleText("月份");

    // 为每个数据点设置标签
    for (auto month : monthLabels.keys()) {
        axisX->append(monthLabels[month], month);
    }

    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue); // 设置标签直接显示在数据点上

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("支出");
    axisY->setLabelFormat("%.2f");

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    chart->legend()->hide();  // 隐藏图例

    lineChartView->setChart(chart);
}

// 获取饼图视图的实现
QGraphicsView *reportWindow::getPieChartView() {
    return pieChartView;
}

// 获取折线图视图的实现
QGraphicsView *reportWindow::getLineChartView() {
    return lineChartView;
}
