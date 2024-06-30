#include "history.h"
#include "ui_history.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include<QFont>
#include <QLabel>
#include "background.h"
#include"quanju.h"
history::history(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::history)
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
this->setWindowTitle("查看多人记账结果");
}

history::~history()
{
    delete ui;
}

void history::on_pushButton_clicked()
{

    auto ans=splitt.balances;
    QString output;
    for (const auto &pair : ans){
        if(pair.second>0)
            output+=pair.first+" 应给出 "+QString::number(pair.second) +"\n";
        else{
            output+=pair.first+" 应获得 "+QString::number(abs(pair.second)) +"\n";
        }
    }


    QFont font;
    font.setPointSize(16);
    QTextEdit *p=ui->textEdit;
    p->setFont(font);
    p->setPlainText(output);
}

