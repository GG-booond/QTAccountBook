#include "splitManager.h"
#include "mainData.h"
#include "oneBill.h"
#include <QDebug>
#include <QDateTime>
#include <fstream>

splitManager::splitManager() : database(mainData()) {}

void splitManager::addOneBill(const oneBill& bill) {
    database.addOneBill(bill);

    balances[bill.getPayer()] -= bill.getAmount();
    double splitAmount = bill.getAmount() / bill.getUsers().size();
    for (const auto& user : bill.getUsers())
        balances[user] += splitAmount;
}

void splitManager::removeOneBill(size_t index) {
    if (index < database.getBills().size()) {
        oneBill tmpBill = *(database.getBills().begin()+index);

        balances[tmpBill.getPayer()] += tmpBill.getAmount();
        double splitAmount = tmpBill.getAmount() / tmpBill.getUsers().size();
        for (const auto& user : tmpBill.getUsers())
            balances[user] += splitAmount;

        database.getBills().erase(database.getBills().begin() + index);
        //saveData();
    }
    else
        qDebug() << "数据不存在";
}
void splitManager::readData_split(){
    ifstream file("/new_QT/newQT/QTproject/split.txt");

    database.bills.clear();

    double amount;
    string dateTime, paymentMethod, currency, category, subcategory, description, payer,users;
    while (file >> amount) {
        file.ignore(); // 忽略\n
        getline(file, dateTime);
        getline(file, paymentMethod);
        getline(file, currency);
        getline(file, category);
        getline(file, subcategory);
        getline(file, description);
        getline(file, payer);

        vector<QString> users;
        string user;
        while (getline(file, user) && !user.empty()) {
            users.push_back(QString::fromStdString(user));
        }

        QString qDateTime = QString::fromStdString(dateTime);
        QString qPaymentMethod = QString::fromStdString(paymentMethod);
        QString qCurrency = QString::fromStdString(currency);
        QString qCategory = QString::fromStdString(category);
        QString qSubcategory = QString::fromStdString(subcategory);
        QString qDescription = QString::fromStdString(description);
        QString qPayer = QString::fromStdString(payer);

        oneBill bill(amount, qDateTime, qPaymentMethod, qCurrency, qCategory, qSubcategory, qDescription, qPayer, users);
        addOneBill(bill);
        //database.addOneBill(bill);
    }

    file.close();

}


void splitManager::saveData_split()const{
    ofstream file("/new_QT/newQT/QTproject/split.txt",ios::trunc);
    auto bills=database.bills;
    if (file.is_open()) {
        for (const auto& bill : bills) {
            file << bill.getAmount() << "\n"
                 << bill.getDateTime().toStdString() << "\n"
                 << bill.getPaymentMethod().toStdString() << "\n"
                 << bill.getCurrency().toStdString() << "\n"
                 << bill.getCategory().toStdString() << "\n"
                 << bill.getSubcategory().toStdString() << "\n"
                 << bill.getDescription().toStdString() << "\n"
                 << bill.getPayer().toStdString() << "\n";
            for (const auto& user : bill.getUsers()) {
                file << user.toStdString() << "\n";
            }
            file << "\n";
        }
        file.close();
    }
}

