#ifndef ONEBILL_H
#define ONEBILL_H

#include <QString>
#include <QDebug>

using namespace std;

class oneBill {
public:
    static void Debugger();

    oneBill(double tmpAmount,
            QString tmpDateTime,
            QString tmpPaymentMethod,
            QString tmpCurrency,
            QString tmpCategory,
            QString tmpSubcategory,
            QString tmpDescription);

    oneBill(double tmpAmount,
            QString tmpDateTime,
            QString tmpPaymentMethod,
            QString tmpCurrency,
            QString tmpCategory,
            QString tmpSubcategory,
            QString tmpDescription,
            QString tmpPayer,
            vector<QString> tmpUsers);

    const double& getAmount() const;
    const QString& getDateTime() const;
    const QString& getPaymentMethod() const;
    const QString& getCurrency() const;
    const QString& getCategory() const;
    const QString& getSubcategory() const;
    const QString& getDescription() const;
    const QString& getPayer() const;
    const vector<QString>& getUsers() const;

    private:
        double amount;
        QString dateTime; //格式需要是yyyy-mm-dd hh:mm:ss
        QString paymentMethod;
        QString currency;
        QString category;
        QString subcategory;
        QString description;
        QString payer;
        vector<QString> users;
    };

#endif // ONEBILL_H
