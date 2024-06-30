#include "fzjilu.h"
#include "ui_fzjilu.h"
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QString>
#include<QDebug>
#include<QDateEdit>
#include<QDateTime>
#include "background.h"
#include"quanju.h"
fzjilu::fzjilu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fzjilu)
{

    QLabel *imagebackground=new QLabel(this);
    QPixmap pixmap(background::file_path);
    if(!pixmap.isNull()){//成功加载
        imagebackground->resize(800,600);
        imagebackground->setPixmap(pixmap.scaled(imagebackground->size()));
    }
    else{
        qDebug()<<"背景未成功加载";
    }
    QDateTime cur=QDateTime::currentDateTime();

    ui->setupUi(this);
    this->setWindowTitle("添加一笔多人记账");
    ui->dateTimeEdit->setDateTime(cur);
}

fzjilu::~fzjilu()
{
    delete ui;
}

//取消按钮
void fzjilu::on_pushButton_2_clicked()
{
    this->close();
}

//完成按钮
void fzjilu::on_pushButton_clicked()
{
    //按下按钮来保存数据
    QString str_summoney,payman,allman,goal,kind,way,date;//总金额 支付人 所有人 用途 币种 支付方式
    str_summoney=ui->lineEdit_3->text();
    payman=ui->lineEdit_5->text();
    allman=ui->lineEdit_4->text();
    QStringList part=allman.split(" ");
    int l=part.size();
    vector<QString>user;
    for(int i=0;i<l;i++){
        user.push_back(part[i]);
    }
    goal=ui->comboBox_3->currentText();
    double sum_money=str_summoney.toDouble();
    int sum_people=ui->spinBox->value();
    kind=ui->comboBox->currentText();
    way=ui->comboBox_2->currentText();
    QDateTime now_date=ui->dateTimeEdit->dateTime();
    date=now_date.toString("yyyy-MM-dd hh:mm:ss");
    oneBill tem(sum_money,date,way,kind,goal," "," ",payman,user);
    splitt.addOneBill(tem);
    splitt.saveData_split();
    this->close();
}
