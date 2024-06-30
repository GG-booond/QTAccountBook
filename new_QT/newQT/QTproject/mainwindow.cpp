#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addone.h"
#include "ui_addone.h"
#include "QMessageBox"
#include "fenzhangjiemian.h"
#include <qlabel.h>
#include "planshow.h"
#include <QPixmap>
#include "planning.h"
#include "background.h"
#include "settings.h"
#include "ui_settings.h"
#include "mainData.h"
#include "quanju.h"
#include "saybills.h"
#include <QCheckBox>
#include <QFileDialog>
#include <direct.h>
#include "reportWindow.h"
#include <fstream>

QString background::file_path=back;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //背景处理
    QLabel *imagebackground=new QLabel(this);
    QPixmap pixmap(background::file_path);
    if(!pixmap.isNull()){//成功加载
        imagebackground->resize(800,600);
        imagebackground->setPixmap(pixmap.scaled(imagebackground->size()));
    }
    else{
        qDebug()<<"背景未成功加载";
    }
    setFixedSize(800,600);

    ui->setupUi(this);
    setButtonStyle();
    this->setWindowTitle("主界面");
    //头部提示处理
    QString data;
    QString path="/new_QT/newQT/QTproject/words/openWords.txt";
    QFile file(path); //path是文件的路径
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"文件未打开!";
    }
    while(!file.atEnd())
    {
        QByteArray array = file.readLine();
        QString str(array);
        // qDebug()<< str;
        data.append(str);
    }
    //ui->textBrowser->setFont(QFont("Arial",12));//设置字体和
    ui->label->setText(data);
    //ui->textBrowser->setText(data);
    QFont font ( "宋体", 16, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    //显示目前状况
    QString moneySum=QString::number(myData.totalAmount,'f',2);
    QLabel *totalSum=new QLabel(moneySum);
    totalSum->setParent(this);//调用函数设置父对象
    totalSum->move(340,-150);
    totalSum->setFont(font);
    vector<QLabel> cateSum;
    //qDebug()<<myData.cataTotalAmounts.size();
    int gapNum=0;
    QFont smallFont("宋体",13,50);
    QFont s("宋体",-1,0);
    for(auto p=myData.cateTotalAmounts.begin();p!=myData.cateTotalAmounts.end();++p){
        QString words=p->first;
        words+="         ";
        words+=QString::number(p->second,'f',2);
        qDebug()<<words;
        QLabel *aLabel=new QLabel(words);
        aLabel->setFont(smallFont);
        aLabel->setParent(this);
        //aLabel->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
        aLabel->move(320,110+gapNum*20);
        aLabel->adjustSize();//自动调整
        allCheck[num++]=new QCheckBox(this);
        //allCheck[gapNum]->setText(p->first);
        //allCheck[gapNum]->setFont(s);
        gapNum++;
    }
    qDebug()<<num;
    for(int i=0;i<num;i++){
        allCheck[i]->move(300,105+i*20);
    }
    ui->pushButton->raise();
    ui->pushButton_2->raise();
    ui->pushButton_3->raise();
    ui->pushButton_4->raise();
   // ui->pushButton_5->raise();

    ui->pushButton_6->raise();
    QLabel *sentense=new QLabel("欢迎使用我们的记账本！");
    ui->statusbar->addWidget(sentense);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()
{
    this->close();//关闭本界面
    AddOne * pic =new AddOne(nullptr);
    pic->show();
    //addAnAccount *pic =new addAnAccount();
    //pic->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    fenzhangjiemian *pic=new fenzhangjiemian();
    pic->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    //delete this;
    this->close();
    Settings *pic=new Settings();
    pic->show();
}


void MainWindow::on_pushButton_6_clicked()
{
    QString Data;
    vector<QString> cateTobesay;
    for(int i=0;i<num;i++){
        if(allCheck[i]->isChecked()==true)
        {
            QString cate;
            int n=0;
            for(auto p=myData.cateTotalAmounts.begin();p!=myData.cateTotalAmounts.end();++p){
                if(n==i){
                    cate=p->first;
                    break;
                }
                n++;
            }
            cateTobesay.push_back(cate);
        }
    }
    //qDebug()<<cateTobesay.size()<<myData.bills.size();
    for(auto p=myData.bills.begin();p!=myData.bills.end();++p){
        bool In=false;
        for(auto pp=cateTobesay.begin();pp!=cateTobesay.end();++pp){
            qDebug()<<p->getCategory()<<*pp;
            if(p->getCategory()==*pp){
                In=true;
                break;
            }
        }
        if(In==true){
            qDebug()<<"adsaf";
            Data+="金额：";
            Data+=QString::number(p->getAmount(),'f',2);
            Data+='\n';
            Data+="时间：";
            Data+=p->getDateTime();
            Data+='\n';
            // getline(file, dateTime);
            // getline(file, paymentMethod);
            // getline(file, currency);
            // getline(file, category);
            // getline(file, subcategory);
            // getline(file, description)
            if(p->getPaymentMethod().size()!=0)
            {
                Data+="支付方式：";
                Data+=p->getPaymentMethod();
                Data+='\n';
            }
            if(p->getCurrency().size()!=0)
            {
                Data+="货币：";
                Data+=p->getCurrency();
                Data+='\n';
            }
            if(p->getCategory().size()!=0)
            {
                Data+="大类：";
                Data+=p->getCategory();
                Data+='\n';
            }
            if(p->getSubcategory().size()!=0)
            {
                Data+="小类：";
                Data+=p->getSubcategory();
                Data+='\n';
            }
                //Data+=p->getDescription();
                //Data+='\n';
            Data+='\n';
            qDebug()<<Data;
        }
    }
    //this->close();
    if(cateTobesay.size()==0){
        QMessageBox::warning(this,"警告","请至少选择一项");
    }
    else
    {
        sayBills* pic=new sayBills(nullptr,Data);
        pic->show();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    reportWindow *w1=new reportWindow(&myData);
    w1->createPieChart();
    w1->createLineChart();
    w1->show();
}


void MainWindow::on_pushButton_7_clicked()
{
    this->close();//关闭本界面
    AddOne * pic =new AddOne(nullptr);
    pic->show();
}


void MainWindow::on_pushButton_clicked()
{
    //this->close();
    planShow *pic =new planShow();
    pic->show();
}

void MainWindow::setButtonStyle(){
    //对add按钮的处理
    ui->pushButton_7->setIcon(QIcon("/new_QT/newQT/QTproject/Image/add.png"));
    ui->pushButton_7->setIconSize(ui->pushButton_7->size());
    QString AddbuttonStyle =
        "QPushButton {"
        "   background-color: transparent;"  // 透明背景
        "   color: white;"                   // 字体颜色
        "   border: none;"                   // 无边框
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 0.3);"  // 悬停时的轻微透明效果
        "}";
    ui->pushButton_7->setStyleSheet(AddbuttonStyle);
    // QString buttonStyle =
    //     "QPushButton {"
    //     "   background-color: #3498db;"  // 按钮背景色
    //     "   color: white;"               // 字体颜色
    //     "   border: none;"               // 无边框
    //     "   padding: 10px;"              // 内边距
    //     "   border-radius: 0px;"         // 去除其他圆角
    //     "}"
    //     "QPushButton::before {"
    //     "   content: '';"
    //     "   position: absolute;"
    //     "   top: 0;"
    //     "   right: 0;"
    //     "   width: 40px;"               // 圆的直径
    //     "   height: 40px;"
    //     "   background-color: #3498db;"
    //     "   border-radius: 20px;"       // 四分之一圆角
    //     "}";

    // ui->pushButton->setStyleSheet(buttonStyle);
    // ui->pushButton_2->setStyleSheet(buttonStyle);
    // ui->pushButton_3->setStyleSheet(buttonStyle);
    // ui->pushButton_4->setStyleSheet(buttonStyle);
    // //ui->pushButton_5->setStyleSheet(buttonStyle);
    // ui->pushButton_6->setStyleSheet(buttonStyle);


}

void MainWindow::on_pushButton_8_clicked()
{
    reportWindow *tempReportWindow = new reportWindow(&myData);
    tempReportWindow->createPieChart();
    tempReportWindow->createLineChart();
    tempReportWindow->show();

    // 确定图片宽度和高度
    int imageWidth = 800; // 图片宽度，根据需要调整
    int pieChartHeight = tempReportWindow->getPieChartView()->height();
    int lineChartHeight = tempReportWindow->getLineChartView()->height();
    int imageHeight = pieChartHeight + lineChartHeight + 300; // 图片高度，加上额外的空间用于文本

    QImage image(imageWidth, imageHeight, QImage::Format_RGB32);
    if (image.isNull()) {
        QMessageBox::critical(this, "错误", "创建图片失败。");
        delete tempReportWindow;
        return;
    }
    image.fill(Qt::white); // 填充背景色

    // 创建QPainter对象
    QPainter painter(&image);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "错误", "QPainter初始化失败。");
        delete tempReportWindow;
        return;
    }

    // 设置字体
    QFont font("Arial", 20);
    painter.setFont(font);
    painter.setPen(Qt::black);

    // 构建要绘制的文本字符串
    QString word;
    for (auto p = myData.cateTotalAmounts.begin(); p != myData.cateTotalAmounts.end(); ++p) {
        if (!p->first.isEmpty() && p->second >= 0) {
            word += p->first;
            word += ": ";
            word += QString::number(p->second, 'f', 2);
            word += "\n";
        }
    }

    // 绘制饼图和折线图
    QPixmap pieChartPixmap = tempReportWindow->getPieChartView()->grab();
    QPixmap lineChartPixmap = tempReportWindow->getLineChartView()->grab();
    painter.drawPixmap(0, 0, pieChartPixmap);
    painter.drawPixmap(0, pieChartHeight, lineChartPixmap);

    // 绘制文本
    if (!word.isEmpty()) {
        // 设置文本绘制的起始位置
        int textStartY = pieChartHeight + lineChartHeight + 10; // 饼图和折线图下方
        painter.drawText(10, textStartY, imageWidth - 20, painter.fontMetrics().height() * word.count("\n"), Qt::AlignLeft | Qt::TextWordWrap, word);
    }

    // 用户选择保存位置和文件名
    QString filter = "Image Files (*.png *.xpm *.jpg);;All Files (*)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存图片"), "combinedImage.png", filter);
    if (!fileName.isEmpty()) {
        if (image.save(fileName)) {
            QMessageBox::information(this, "导出成功", "图片已成功导出到: " + fileName);
        } else {
            QMessageBox::warning(this, "导出失败", "图片保存失败，请检查文件路径是否正确。");
        }
    }

    // 清理资源
    delete tempReportWindow;

}

