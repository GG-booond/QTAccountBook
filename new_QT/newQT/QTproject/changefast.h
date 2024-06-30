#ifndef CHANGEFAST_H
#define CHANGEFAST_H

#include <QWidget>

namespace Ui {
class changeFast;
}

class changeFast : public QWidget
{
    Q_OBJECT

public:
    explicit changeFast(QWidget *parent = nullptr);
    ~changeFast();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::changeFast *ui;
};

#endif // CHANGEFAST_H
