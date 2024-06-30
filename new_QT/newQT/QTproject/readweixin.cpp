#include "readweixin.h"
#include "ui_readweixin.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include<QFont>

readweixin::readweixin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::readweixin)
{
    ui->setupUi(this);
}

readweixin::~readweixin()
{
    delete ui;
}

void readweixin::on_pushButton_clicked()
{
    QString sum_money,man,note,subgoal,usegoal,kind,method,time;
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", ".", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            sum_money=in.readLine().trimmed();
            time=in.readLine().trimmed();
            method=in.readLine().trimmed();
            kind=in.readLine().trimmed();
            usegoal=in.readLine().trimmed();
            subgoal=in.readLine().trimmed();
            note=in.readLine().trimmed();
            man=in.readLine().trimmed();

            file.close();
        }
    }
    QString output;
    output += "总金额： " + sum_money + "\n";
    output += "时间： " + time + "\n";
    output += "支付方式： " + method + "\n";
    output += "币种： " + kind + "\n";
    output += "使用目标： " + usegoal + "\n";
    output += "子目标： " + subgoal + "\n";
    output += "备注： " + note + "\n";
    output += "参与人： " + man + "\n";

    QFont font;
    font.setPointSize(16);
    QTextEdit *p=ui->textEdit;
    p->setFont(font);
    p->setPlainText(output);
}

