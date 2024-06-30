#include "settings.h"
#include "ui_settings.h"
#include <QLabel>
#include "background.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "changefast.h"
#include <fstream>
#include <QFileDialog>
Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
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

    this->setWindowTitle("设置");
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_4_clicked()
{
    //返回
    this->close();
    MainWindow *pic=new MainWindow();
    pic->show();
}


void Settings::on_pushButton_3_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,
                                                    tr("请选择心仪的背景"),
                                                    "D:/new_QT",
                                                    tr("*.jpg;*.png;*.gif"));
    if(fileName.isEmpty()){
        QMessageBox::warning(this,"Warning!","未成功更换壁纸!");
    }
    else{//处理从文件中导入的问题
        QMessageBox::information(this,tr("提示"),"已经成功更换壁纸。<br>""新的壁纸已经加载完毕!");
        background::change_path(fileName);
        ofstream file("/new_QT/newQT/QTproject/words/path.txt");
        if(!file.is_open()){
            qDebug()<<"未成功写入路径文件";
        }
        else{
            file<<fileName.toStdString();
            file.close();
        }
        //重新打开
        this->close();
        Settings *pic=new Settings();
        pic->show();
    }
}


void Settings::on_pushButton_2_clicked()
{
    changeFast *pic=new changeFast();
    pic->show();
}


void Settings::on_pushButton_5_clicked()
{
    ofstream truncateFile("/new_QT/newQT/QTproject/data.txt", ios::trunc);
    if(!truncateFile.is_open())
        qDebug()<<"未成功清空";
    else{
        QMessageBox::information(this,"提醒","已经成功清除账单<br>""请重新打开程序以查看");
        this->close();
    }
    truncateFile.close();
}


void Settings::on_pushButton_clicked()
{
    ofstream truncateFile("/new_QT/newQT/QTproject/words/classes.txt", ios::trunc);
    if(!truncateFile.is_open())
        qDebug()<<"未成功清空";
    else{
        QMessageBox::information(this,"提醒","已经成功清除计划<br>""请重新打开程序以查看");
        this->close();
    }
    truncateFile.close();
}

