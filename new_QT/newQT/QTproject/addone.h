#ifndef ADDONE_H
#define ADDONE_H

#include <QWidget>
#include"mainData.h"
namespace Ui {
class AddOne;
}

class AddOne : public QWidget
{
    Q_OBJECT

public:
    explicit AddOne(QWidget *parent = nullptr);
    //void loadcombox();
    ~AddOne();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AddOne *ui;
};

#endif // ADDONE_H
