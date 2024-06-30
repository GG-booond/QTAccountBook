#include "mainwindow.h"
#include "oneBill.h"
#include <QApplication>
#include "mainData.h"
#include "background.h"
#include "mainData.cpp"
#include "quanju.h"//用全局文件来解决所有文件都需要使用的问题

int main(int argc, char *argv[])
{
    myData.readData();
    //myData.saveData();
    ifstream ff("/new_QT/newQT/QTproject/words/path.txt");
    if(!ff.is_open()){
        qDebug()<<"未正确读入背景路径";
    }
    else{
        string tmpback;
        getline(ff,tmpback);
        back=QString::fromStdString(tmpback);
        background::change_path(back);
    }
    QApplication a(argc, argv);
    MainWindow w(nullptr);//将这个数据指针传给mainwindow
    w.show();
    //oneBill::Debugger();

    return a.exec();
}
