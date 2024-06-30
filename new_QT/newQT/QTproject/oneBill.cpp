#include "oneBill.h"
#include <QDateTime>
#include <QDebug>

using namespace std;

void oneBill::Debugger() {
    QDateTime curr = QDateTime::currentDateTime();
    qDebug() << curr.toString();
}

const double& oneBill::getAmount() const {
    return amount;
}
const QString& oneBill::getDateTime() const {
    return dateTime;
}
const QString& oneBill::getPaymentMethod() const {
    return paymentMethod;
}
const QString& oneBill::getCurrency() const {
    return currency;
}
const QString& oneBill::getCategory() const {
    return category;
}
const QString& oneBill::getSubcategory() const {
    return subcategory;
}
const QString& oneBill::getDescription() const {
    return description;
}
const QString& oneBill::getPayer() const {
    return payer;
}
const vector<QString>& oneBill::getUsers() const {
    return users;
}

oneBill::oneBill(double tmpAmount,
                 QString tmpDateTime,
                 QString tmpPaymentMethod,
                 QString tmpCurrency,
                 QString tmpCategory,
                 QString tmpSubcategory,
                 QString tmpDescription):
    amount(tmpAmount),
    dateTime(tmpDateTime),
    paymentMethod(tmpPaymentMethod),
    currency(tmpCurrency),
    category(tmpCategory),
    subcategory(tmpSubcategory),
    description(tmpDescription){}

oneBill::oneBill(double tmpAmount,
        QString tmpDateTime,
        QString tmpPaymentMethod,
        QString tmpCurrency,
        QString tmpCategory,
        QString tmpSubcategory,
        QString tmpDescription,
        QString tmpPayer,
        vector<QString> tmpUsers):
    amount(tmpAmount),
    dateTime(tmpDateTime),
    paymentMethod(tmpPaymentMethod),
    currency(tmpCurrency),
    category(tmpCategory),
    subcategory(tmpSubcategory),
    description(tmpDescription),
    payer(tmpPayer),
    users(tmpUsers) {}
