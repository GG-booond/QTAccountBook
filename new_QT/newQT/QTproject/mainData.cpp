#include "mainData.h"
#include "categoryManager.h"
#include "oneBill.h"
#include <vector>
#include <map>
#include <fstream>
#include <QDebug>
#include <QDate>

using namespace std;

vector<mainData*> mainData::allMainDatas;

mainData::mainData() {
    bills = vector<oneBill>();
    totalAmount = 0;
    auto categories = categoryManager::getCategories();
    for (auto it = categories.begin(); it != categories.end(); ++it) {
        QString key = it->first;
        cateTotalAmounts[key] = 0;
    }
    allMainDatas.push_back(this);
}

bool compareByDateTime(const oneBill& bill1, const oneBill& bill2) {
    return bill1.getDateTime() < bill2.getDateTime();
}

void mainData::addOneBill(const oneBill& bill) {
    bills.push_back(bill);
    totalAmount += bill.getAmount();
    cateTotalAmounts[bill.getCategory()] += bill.getAmount();
    sort(bills.begin(), bills.end(), compareByDateTime);
    saveData();
}

void mainData::removeOneBill(size_t index) {
    if (index < bills.size()) {
        bills.erase(bills.begin() + index);
        saveData();
    }
    else
        qDebug() << "数据不存在";
}

vector<oneBill>& mainData::getBills(){
    return bills;
}

void mainData::saveData() const
{
    ofstream file("/new_QT/newQT/QTproject/data.txt",ios::trunc);
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


void mainData::readData()
{
    ifstream file("/new_QT/newQT/QTproject/data.txt");

    bills.clear();
    
    double amount;
    string dateTime, paymentMethod, currency, category, subcategory, description, payer;
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
    }

    file.close();
}

void mainData::updateCateTotalAmounts(const QString& category, double amount) {
    cateTotalAmounts[category] += amount;
}

const double& mainData::getTotalAmount() const {
    return totalAmount;
}

const map<QString, double>& mainData::getCateTotalAmounts() const {
    return cateTotalAmounts;
}

map<QString, double> mainData::getMonthlyExpenses() const {
    map<QString, double> monthlyExpenses;
    for (const auto& bill : bills) {
        QString month = bill.getDateTime().left(7); // Assuming date format is YYYY-MM
        monthlyExpenses[month] += bill.getAmount();
    }
    return monthlyExpenses;
}
