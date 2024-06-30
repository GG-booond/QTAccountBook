#include "planning.h"
#include "ui_planning.h"
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include "background.h"
#include "planshow.h"
#include "quanju.h"
#include "QDate"
#include "QDateEdit"
planning::planning(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::planning)
{
    // 背景处理
    QLabel *imagebackground = new QLabel(this);
    QPixmap pixmap(background::file_path);
    if (!pixmap.isNull()) { // 成功加载
        imagebackground->resize(800, 600);
        imagebackground->setPixmap(pixmap.scaled(imagebackground->size()));
    } else {
        qDebug() << "背景未成功加载";
    }

    ui->setupUi(this);
     ui->dateEdit->setDate(QDate::currentDate()); // 设置为今天的日期
    this->setWindowTitle("修改我的计划");
    // 连接 QDialogButtonBox 的 accepted 信号到槽函数
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &planning::on_buttonBox_accepted);
    ui->lineEdit->setPlaceholderText("类别");
        ui->lineEdit_2->setPlaceholderText("计划金额");
    // 加载文件内容到 ComboBox
    loadPlansFromFile();
}

planning::~planning()
{
    delete ui;
}

void planning::loadPlansFromFile()
{
    // 清空 ComboBox 内容
    ui->comboBoxPlans->clear();
    for (auto p = plans.begin(); p != plans.end(); ++p) {
        QString line = p.key();
        if (line != sumALLplans)
            ui->comboBoxPlans->addItem(line);
    }
}

void planning::on_buttonBox_accepted()
{
    // 获取总计划数目
    QString totalPlansText = ui->textEditPlanALL->text();
    double totalPlans = totalPlansText.toDouble();
    if (totalPlansText.isEmpty()) {
        totalPlans = 0;
    }

    // 获取计划名称和数目
    QString planName = ui->lineEdit->text();
    QString planValueStr = ui->lineEdit_2->text();
    double planValue = planValueStr.toDouble();

    // 添加新计划到 QMap
    if ((!planName.isEmpty() )&& (!planValueStr.isEmpty())) {
        if(!plans.contains(planName))
            plans.insert(planName,planValue);
    }

    // 获取用户选择的类别并更新其数值
    QString selectedCategory = ui->comboBoxPlans->currentText();
    QString newValueStr = ui->textEditPlan->text();
    double newValue = newValueStr.toDouble();
    if (newValue&&plans.contains(selectedCategory)) {
        plans[selectedCategory] = newValue;
    }

    // 计算计划总和
    double calculatedTotal = 0;
    for (auto it = plans.begin(); it != plans.end(); ++it) {
        if (it.key() != sumALLplans) {
            calculatedTotal += it.value();
        }
    }

    if (totalPlans != 0 && calculatedTotal != totalPlans) {
        QMessageBox::warning(this, "Warning", "总和错误！");
        return;
    } else if (totalPlans == 0) {
        totalPlans = calculatedTotal;
    }
    if(ui->dateEdit->date()!=QDate::currentDate())
        saveDateToFile();
    // 保存总计划数目和计划详情到文件
    QFile file("/new_QT/newQT/QTproject/words/classes.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << sumALLplans << ": " << totalPlans << "\n";
        QMapIterator<QString, double> i(plans);
        while (i.hasNext()) {
            i.next();
            if (i.key() != sumALLplans) {
                qDebug() << i.key() << ": " << i.value() << "\n";
                out << i.key() << ": " << i.value() << "\n";
            }
        }
        file.close();
        qDebug() << "计划已保存到文件";
    } else {
        qDebug() << "无法打开文件进行写入";
    }

    // 更新 ComboBox 内容
    //loadPlansFromFile();
    this->close();
}

void planning::on_buttonBox_rejected()
{
    this->close();
    planShow *pic = new planShow();
    pic->show();
}
void planning::saveDateToFile()
{
    QFile file("/new_QT/newQT/QTproject/words/plandate.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for writing.";
        return;
    }

    QTextStream out(&file);
    out << ui->dateEdit->date().toString("yyyy-MM-dd");
    file.close();
}
