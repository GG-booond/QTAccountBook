#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>
#include <QGraphicsWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "mainData.h"

class reportWindow : public QMainWindow {
    Q_OBJECT

public:
    reportWindow(mainData* database, QWidget *parent = nullptr);
    void createPieChart();
    void createLineChart();
    QGraphicsView *getPieChartView();  // 获取饼图视图
    QGraphicsView *getLineChartView();  // 获取折线图视图

private:
    QChart *pieChart;
    QChart *lineChart;
    QChartView *pieChartView;
    QChartView *lineChartView;
    mainData *database;
};

#endif // REPORTWINDOW_H
