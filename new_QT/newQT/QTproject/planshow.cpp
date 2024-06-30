#include "planshow.h"
#include "ui_planshow.h"
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QFont>
#include <QPushButton>
#include <QDateEdit> // 添加日期编辑器头文件

#include "background.h"
#include "planning.h"
#include "quanju.h"

planShow::planShow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::planShow)
    , mainLayout(new QVBoxLayout(this))
    , buttonLayout(new QHBoxLayout())
    , dateLayout(new QHBoxLayout()) // 添加日期布局的初始化
{
    QLabel *imagebackground = new QLabel(this);
    QPixmap pixmap(background::file_path);
    if (!pixmap.isNull()) { // 成功加载背景图片
        imagebackground->resize(800, 600);
        imagebackground->setPixmap(pixmap.scaled(imagebackground->size()));
    } else {
        qDebug() << "背景未成功加载";
    }
    ui->setupUi(this);
    this->setWindowTitle("查看我的计划");
    // 设置整体字体
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(16);
    this->setFont(font);

    // 设置主布局
    setLayout(mainLayout);

    // 加载文件内容到布局
    loadPlansFromFile();


    // 添加显示日期的 QLabel 和 QDateEdit 在最后一行
    QLabel *labelDDL = new QLabel("计划DDL：", this);
    dateLayout->addWidget(labelDDL);

    dateEdit = new QDateEdit(this);
    dateLayout->addWidget(dateEdit);
    dateEdit->setEnabled(false);
    // 设置日期编辑器的日期为文件中的日期
    QFile dateFile("/new_QT/newQT/QTproject/words/plandate.txt");
    if (dateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&dateFile);
        QString dateString = in.readLine();
        QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
        dateEdit->setDate(date);
        dateFile.close();
    } else {
        qDebug() << "无法打开日期文件进行读取";
    }

    // 将日期布局添加到主布局的最后一行
    mainLayout->addLayout(dateLayout);
    mainLayout->addStretch(); // 添加弹性空间，将日期布局推到底部
    // 创建一个水平布局用于放置“修改计划”按钮
    buttonLayout->addStretch(); // 添加弹性空间将按钮推到右边
    QPushButton *buttonEditPlan = new QPushButton("修改计划", this);
    buttonEditPlan->setObjectName("buttonEditPlan");
    buttonLayout->addWidget(buttonEditPlan);

    // 将按钮布局添加到主布局的底部
    mainLayout->addLayout(buttonLayout);

    // 连接“修改计划”按钮的点击事件到槽函数
    connect(buttonEditPlan, &QPushButton::clicked, this, &planShow::on_buttonEditPlan_clicked);

}

planShow::~planShow()
{
    delete ui;
}

void planShow::loadPlansFromFile()
{
    // 清空主布局中的所有控件（除了最后一行的按钮布局和日期布局）
    while (QLayoutItem *item = mainLayout->takeAt(0)) {
        if (item->layout() == buttonLayout || item->layout() == dateLayout) {
            mainLayout->addItem(item); // 保留按钮布局和日期布局
            continue;
        }
        if (item->layout()) {
            delete item->layout();
        } else if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    plans.clear();
    // 读取文件内容
    QFile ffile("/new_QT/newQT/QTproject/words/classes.txt");
    if (ffile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&ffile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(':');
            if (parts.size() == 2) {
                QString category = parts[0].trimmed();
                double value = parts[1].trimmed().toDouble();
                plans[category] = value;
            }
        }
        ffile.close();
        qDebug() << "计划已加载";
    } else {
        qDebug() << "无法打开文件进行读取";
    }
    auto tmp=myData.cateTotalAmounts;
    for (auto pp=tmp.begin();pp!=tmp.end();pp++){
        bool has=false;
        for(auto p=plans.begin();p!=plans.end();++p){
            if(pp->first==p.key()){
                has=true;
                break;
            }
        }
        if (!has){
            plans[pp->first]=pp->second;
        }
    }
    //bool showSum=false;
    for(auto p=plans.begin();p!=plans.end();p++){
        if(p.key()==sumALLplans)
        {
            // 创建文本提示
            QString word=p.key();
            word+="  ";
            word+=QString::number(myData.getTotalAmount());
            word+='/';
            word+=QString::number(p.value());
            QLabel *label = new QLabel(word, this);
            mainLayout->addWidget(label);
            double progress=100*(myData.getTotalAmount()/(p.value()));
            qDebug()<<progress;
            // 创建进度条
            QProgressBar *progressBar = new QProgressBar(this);
            progressBar->setRange(0, 100);
            progressBar->setValue(progress);
            mainLayout->addWidget(progressBar);
        }
    }
    for(auto p=plans.begin();p!=plans.end();p++){
        if(p.key()!=sumALLplans)
        {
            // 创建文本提示
            QString word=p.key();
            word+="  ";
            word+=QString::number(myData.cateTotalAmounts[p.key()]);
            word+='/';
            word+=QString::number(p.value());
            QLabel *label = new QLabel(word, this);
            mainLayout->addWidget(label);
            double progress=100*(myData.cateTotalAmounts[p.key()]/(p.value()));
            qDebug()<<progress;
            // 创建进度条
            QProgressBar *progressBar = new QProgressBar(this);
            progressBar->setRange(0, 100);
            progressBar->setValue(progress);
            mainLayout->addWidget(progressBar);
        }}
}

void planShow::on_buttonEditPlan_clicked()
{
    this->close();
    planning *pic = new planning();
    pic->show();
}
