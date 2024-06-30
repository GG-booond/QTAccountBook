#ifndef SAYBILLS_H
#define SAYBILLS_H

#include <QWidget>

namespace Ui {
class sayBills;
}

class sayBills : public QWidget
{
    Q_OBJECT

public:
    explicit sayBills(QWidget *parent = nullptr,QString data=QString());
    ~sayBills();

private:
    Ui::sayBills *ui;
};

#endif // SAYBILLS_H
