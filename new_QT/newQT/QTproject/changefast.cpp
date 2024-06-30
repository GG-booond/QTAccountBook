#include "changefast.h"
#include "ui_changefast.h"
#include "background.h"
#include <fstream>
#include <QMessageBox>
#include "settings.h"
changeFast::changeFast(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changeFast)
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
    ui->setupUi(this);
    this->setWindowTitle("更改快速记账模版");
}

changeFast::~changeFast()
{
    delete ui;
}

void changeFast::on_pushButton_2_clicked()
{
    QString beizhu,moneyType,payWay,cate,subCate;
    beizhu=ui->lineEdit_2->text();
    moneyType=ui->lineEdit_3->text();
    cate=ui->lineEdit_4->text();
    subCate=ui->lineEdit_5->text();
    payWay=ui->comboBox->currentText();
    //QDateTime inTime= ui->dateTimeEdit->dateTime();
    if(beizhu.isEmpty())
        beizhu="None";
    if(subCate.isEmpty())
        subCate="None";
    if(moneyType.isEmpty()||cate.isEmpty()||payWay.isEmpty())
    {
        QMessageBox::warning(this,"Warning!","请输入正确的模版！");
    }
    else
    {
        ofstream file("/new_QT/newQT/QTproject/words/template.txt");
        if(!file)
            qDebug()<<"未成功记录快速记账模版";
        if (file.is_open()) {
            file << beizhu.toStdString() <<"\n"
                 <<moneyType.toStdString()<<"\n"
                 <<cate.toStdString()<<"\n"
                 <<subCate.toStdString()<<"\n"
                 <<payWay.toStdString()<<"\n";
            file.close();
        }
        this->close();
        Settings* pic=new Settings();
        pic->show();
    }
}


void changeFast::on_pushButton_clicked()
{
    this->close();
}

