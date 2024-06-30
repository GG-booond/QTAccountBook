#include "addone.h"
#include "ui_addone.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addbyhand.h"
//#include "mainwindow.cpp"
#include "ui_addbyhand.h"
#include <QFileDialog>
#include <QtWidgets/qmessagebox.h>
#include <QLabel>
#include "quanju.h"
#include "background.h"
#include <QDatetime>
#include "readweixin.h"
#include <fstream>
AddOne::AddOne(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddOne)
{

    //设置背景
    QLabel *imagebackground=new QLabel(this);
    QPixmap pixmap(background::file_path);
    if(!pixmap.isNull()){//成功加载
        imagebackground->resize(400,300);
        imagebackground->setPixmap(pixmap.scaled(imagebackground->size()));
    }
    else{
        qDebug()<<"背景未成功加载";
    }
    //ui->lineEdit->setPlaceholderText("请输入金额");
    ui->setupUi(this);
    this->setWindowTitle("记一笔账");
}

AddOne::~AddOne()
{
    delete ui;
}

void AddOne::on_pushButton_3_clicked()
{
    this->close();//关闭自己界面
    MainWindow *pic=new MainWindow();
    pic->show();
}


void AddOne::on_pushButton_2_clicked()
{
    this->close();
    AddByHand * pic=new AddByHand();
    pic->show();
}


bool checktime(const QStringList &list) {
    // 确保列表至少有一个元素
    if (list.isEmpty()) return false;

    // 使用正则表达式检查第一个元素是否是时间格式
    QRegularExpression timeRegex(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");
    QRegularExpressionMatch match = timeRegex.match(list.first());

    // 如果匹配成功（即match是有效的），则返回true
    return match.isValid();
}
void AddOne::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open CSV File"), "",
                                                    tr("CSV Files (*.csv)"));

    if (fileName.isEmpty())
        return; // 如果没有选择文件，则返回

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return; // 如果无法打开文件，则返回
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine(); // 读取一行
        QStringList fields = line.split(","); // 按逗号分割字段
        if(fields[0].size()==19){
            qDebug()<<fields[0]; // 打印字段到控制台 << fields<<" "
            if(fields[4]=="收入"){
                QString cleanedString = fields[5].mid(1);
                double money=cleanedString.toDouble();
                oneBill tem(-money,fields[0],"微信支付","人民币",fields[1],fields[3],fields[7]);
                myData.addOneBill(tem);
            }
            else{
                QString cleanedString = fields[5].mid(1);
                double money=cleanedString.toDouble();
                oneBill tem(money,fields[0],"微信支付","人民币",fields[1],fields[3],fields[7]);
                myData.addOneBill(tem);
            }
        }
    }
    file.close();
    myData.saveData();
    readweixin *p=new readweixin;
    //p->show();
}

void AddOne::on_pushButton_4_clicked()
{
    QString money=ui->lineEdit->text();//这里需要根据金额和已有快速模版加入总账单
    if(money.size()!=0)
    {
        QString beizhu,moneyType,payWay,cate,subCate;
        QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ifstream file("/new_QT/newQT/QTproject/words/template.txt");
        if(!file)
            qDebug()<<"未成功记录快速记账模版";
        if (file.is_open()) {
            string dateTime, paymentMethod, currency, category, subcategory, description;
            getline(file, description);
            getline(file, currency);
            getline(file, category);
            getline(file, subcategory);
            getline(file, paymentMethod);

            payWay= QString::fromStdString(paymentMethod);
            moneyType= QString::fromStdString(currency);
            cate = QString::fromStdString(category);
            subCate = QString::fromStdString(subcategory);
            beizhu = QString::fromStdString(description);
            file.close();
        }
        myData.addOneBill(oneBill(money.toDouble(),time,payWay,moneyType,cate,subCate,beizhu));
        QMessageBox::information(this,tr("提示"),"已经成功记账。<br>""返回以查看新的账单!");
        this->close();
        myData.saveData();
        MainWindow *pic=new MainWindow();
        pic->show();
    }
}
