#ifndef MAINDATA_H
#define MAINDATA_H

#include "oneBill.h"
#include <vector>
#include <map>
#include <QString>

using namespace std;

class mainData {
public:
    mainData();

    void addOneBill(const oneBill& bill);
    void removeOneBill(size_t index);

    vector<oneBill>& getBills();
    void saveData() const;
    void readData();
    void updateCateTotalAmounts(const QString& category, double amount); //修改（赋初值）接口

    const double& getTotalAmount() const;
    const map<QString, double>& getCateTotalAmounts() const;

    static vector<mainData*> allMainDatas;

    map<QString, double> getMonthlyExpenses() const;
    vector<oneBill> bills;
    double totalAmount;
    map<QString, double> cateTotalAmounts;
};


#endif // MAINDATA_H
