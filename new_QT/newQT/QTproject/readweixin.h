#ifndef READWEIXIN_H
#define READWEIXIN_H

#include <QDialog>

namespace Ui {
class readweixin;
}

class readweixin : public QDialog
{
    Q_OBJECT

public:
    explicit readweixin(QWidget *parent = nullptr);
    ~readweixin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::readweixin *ui;
};

#endif // READWEIXIN_H
