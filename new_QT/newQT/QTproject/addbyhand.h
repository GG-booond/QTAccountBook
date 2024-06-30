#ifndef ADDBYHAND_H
#define ADDBYHAND_H

#include <QWidget>

namespace Ui {
class AddByHand;
}

class AddByHand : public QWidget
{
    Q_OBJECT

public:
    explicit AddByHand(QWidget *parent = nullptr);
    ~AddByHand();
    void loadcombox();
    void setSubcates();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::AddByHand *ui;
};

#endif // ADDBYHAND_H
