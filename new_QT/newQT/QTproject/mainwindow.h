#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainData.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QCheckBox>
#include <QFile>
//#include "background.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QCheckBox* allCheck[100]{};
     int num=0;
    void setButtonStyle();
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

   // void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

private:
    QTextEdit   *textEdit;  // 用于显示文件内容的文本框
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
