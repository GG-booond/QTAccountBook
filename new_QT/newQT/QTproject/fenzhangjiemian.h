#ifndef FENZHANGJIEMIAN_H
#define FENZHANGJIEMIAN_H

#include <QWidget>

namespace Ui {
class fenzhangjiemian;
}

class fenzhangjiemian : public QWidget
{
    Q_OBJECT

public:
    explicit fenzhangjiemian(QWidget *parent = nullptr);
    ~fenzhangjiemian();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::fenzhangjiemian *ui;
};

#endif // FENZHANGJIEMIAN_H
