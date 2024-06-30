#include "addbyhand.h"
#include "ui_addbyhand.h"
#include "addone.h"
#include "ui_addone.h"
#include <QtWidgets/qmessagebox.h>
#include<QLabel>
#include<QFile>
#include "background.h"
#include <QDateEdit>
#include "oneBill.h"
#include "quanju.h"
#include "categoryManager.h"

AddByHand::AddByHand(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddByHand)
{

    QLabel *imagebackground=new QLabel(this);
    QPixmap pixmap(background::file_path);
    if(!pixmap.isNull()){//成功加载
        imagebackground->resize(400,300);
        imagebackground->setPixmap(pixmap.scaled(imagebackground->size()));
    }
    else{
        qDebug()<<"背景未成功加载";
    }
    ui->setupUi(this);
    setSubcates();
    // 在界面初始化时设置 lineEdit 初始状态
    ui->lineEdit_virtual->setEnabled(false);
    ui->lineEdit_virtual->setVisible(false);//初始不可见
    loadcombox();

    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){
                ui->lineEdit_virtual->setVisible(true);
                // 如果用户选择了 "自定义" 选项，启用 lineEdit 输入
                if (index == ui->comboBox_2->count() - 1) { // 最后一个选项是 "自定义"
                    ui->lineEdit_virtual->setEnabled(true);
                    // 在初始化方法中设置样式表
                    ui->comboBox_2->setStyleSheet(
                        "QComboBox#comboBox_2 {"
                        "    background-color: rgba(255, 255, 255, 0); /* 完全透明 */"
                        "    border: none; /* 去掉边框 */"
                        "    color: rgba(0, 0, 0, 0); /* 文字颜色完全透明 */"
                        "    selection-color: black; /* 设置选中文本的颜色 */"
                        "}"
                        "QComboBox#comboBox_2::down-arrow {"
                        "    image: url(:/images/down-arrow.png); /* 设置箭头图标 */"
                        "    width: 12px; /* 图标宽度 */"
                        "    height: 12px; /* 图标高度 */"
                        "    subcontrol-position: right; /* 位于右侧 */"
                        "    subcontrol-origin: padding; /* 在内边距区域 */"
                        "    right: 10px; /* 调整图标位置 */"
                        "    top: 50%; /* 垂直居中 */"
                        "    margin-top: -6px; /* 垂直居中的偏移 */"
                        "}"
                        "QComboBox#comboBox_2:!enabled {"
                        "    background-color: rgba(255, 255, 255, 0); /* 完全透明 */"
                        "    color: rgba(0, 0, 0, 0); /* 文字颜色完全透明 */"
                        "}"
                        );
                    //ui->comboBox_4->addItem("其它");
                    //qDebug() << "db1";
                } else {
                    qDebug() << "db2";
                    ui->lineEdit_virtual->setEnabled(false);
                    ui->lineEdit_virtual->setVisible(false);
                    // 清除 comboBox_2 的样式表
                    ui->comboBox_2->setStyleSheet("");
                }
                //qDebug() << "db3";
            });

    ui->lineEdit->setPlaceholderText("请输入金额...");
    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit_2->setPlaceholderText("请输入用途...");//应该加选项
    ui->lineEdit_2->setClearButtonEnabled(true);
    QDateTime current=QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(current);//将时间表设置为当前时间
      this->setWindowTitle("手动添加一笔");
}

AddByHand::~AddByHand()
{
    delete ui;
}

void AddByHand::on_pushButton_clicked()
{
    this->close();
    AddOne *pic=new AddOne();
    pic->show();
}


void AddByHand::on_pushButton_2_clicked()
{
    QString money,beizhu,moneyType,payWay,cate,subCate;
    money=ui->lineEdit->text();
    beizhu=ui->lineEdit_2->text();
    moneyType=ui->comboBox_3->currentText();
    cate=ui->comboBox_2->currentText();
    subCate=ui->comboBox_4->currentText();//(*)
    payWay=ui->comboBox->currentText();
    if(cate=="输入新大类...") {
        cate=ui->lineEdit_virtual->text();
        categoryManager tmpCate;
        tmpCate.addCategory(cate);
        tmpCate.addSubcategory(cate, "其它");
    }
    if(money.size()!=0){//说明成功记账
        QDateTime inTime= ui->dateTimeEdit->dateTime();
        myData.addOneBill(oneBill(money.toDouble(),inTime.toString("yyyy-MM-dd hh:mm:ss"),payWay,moneyType,cate,subCate,beizhu));
        this->close();
        AddOne *pic=new AddOne();
        pic->show();
        myData.saveData();
    }
    else{
        //QMessageBox::StandardButton reply;
        //reply=QMessageBox::information(this,tr("Warning"),"请输入正确的金额！");
        QMessageBox::warning(this,"Warning!","请输入正确的金额！");
    }
}

void AddByHand::loadcombox() {
    categoryManager tmpCate;
    Categories C = tmpCate.getCategories();
    qDebug() << C.size();
    //QString origin[l]{"学习","恋爱","运动","娱乐"};//修改时记得修改下面两个for循环的长度
    for (auto it = C.rbegin(); it != C.rend(); ++it)
    {
        qDebug() << it->first;
        if (it->first != "其它")
            ui->comboBox_2->addItem(it->first);
    }
    qDebug() << "test630";
    QFile ffile("/new_QT/newQT/QTproject/words/classes.txt");
    if (ffile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&ffile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(':');
            if (parts.size() == 2) {
                QString category = parts[0].trimmed();
                //double value = parts[1].trimmed().toDouble();
                bool inOrigin=false;
                for (auto it = C.begin(); it != C.end(); ++it)
                    if (category == it->first){
                        inOrigin=true;
                        break;
                    }
                if (!inOrigin&&category!=sumALLplans){
                    ui->comboBox_2->addItem(category);
                    tmpCate.addCategory(category);
                    tmpCate.addSubcategory(category, "其它");
                }
            }
        }
        ui->comboBox_2->addItem("其它");
        ui->comboBox_2->addItem("输入新大类...");
        ffile.close();
        qDebug() << "计划已加载";
    } else {
        qDebug() << "无法打开文件进行读取";
    }
}

void AddByHand::setSubcates()
{
    ui->comboBox_4->clear();
    QString currCate = ui->comboBox_2->currentText();
    //qDebug() << currCate;
    Categories C = categoryManager().getCategories();
    if (C.find(currCate) != C.end())
    {
        Subcategories tmpSubcate = C[currCate];
        for (int i = 0; i < tmpSubcate.size(); ++i)
            ui->comboBox_4->addItem(tmpSubcate[i]);
    }
    if (currCate == "输入新大类...")
        ui->comboBox_4->addItem("其它");
}

void AddByHand::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    setSubcates();
}

