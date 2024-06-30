#include "fenzhangjiemian.h"
#include "ui_fenzhangjiemian.h"
#include<QFile>
#include<QFileDialog>
#include <QStringList>
#include <QDebug>
#include <QRegularExpression>
#include<QMessageBox>
#include<vector>
#include"fzjilu.h"
#include"history.h"
#include"mainData.h"
#include"quanju.h"
#include"readweixin.h"
#include <QLabel>
#include "background.h"
#include "mainwindow.h"
fenzhangjiemian::fenzhangjiemian(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fenzhangjiemian)
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
     this->setWindowTitle("多人记账模式");
    //myData.readData();
    splitt.readData_split();
}

fenzhangjiemian::~fenzhangjiemian()
{
    delete ui;
}

void fenzhangjiemian::on_pushButton_clicked()
{


    fzjilu * jilufz=new fzjilu;
    jilufz->show();
}


void fenzhangjiemian::on_pushButton_3_clicked()
{
    this->close();
    MainWindow *pic=new MainWindow();
    pic->show();
}


void fenzhangjiemian::on_pushButton_2_clicked()
{
    history * his=new history;
    his->show();

}

void fenzhangjiemian::on_pushButton_4_clicked()
{

}

