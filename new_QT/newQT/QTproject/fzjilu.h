#ifndef FZJILU_H
#define FZJILU_H

#include <QDialog>

namespace Ui {
class fzjilu;
}

class fzjilu : public QDialog
{
    Q_OBJECT

public:
    explicit fzjilu(QWidget *parent = nullptr);
    ~fzjilu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

   // void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::fzjilu *ui;
};

#endif // FZJILU_H
