#include "saybills.h"
#include "ui_saybills.h"

sayBills::sayBills(QWidget *parent,QString data)
    : QWidget(parent)
    , ui(new Ui::sayBills)
{

    ui->setupUi(this);
    ui->textBrowser->setText(data);
     this->setWindowTitle("查看详细");
}

sayBills::~sayBills()
{
    delete ui;
}
