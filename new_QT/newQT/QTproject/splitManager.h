#ifndef SPLITMANAGER_H
#define SPLITMANAGER_H

#include "mainData.h"
#include <map>
#include <QString>

using namespace std;

class splitManager {
public:
    splitManager();

    void addOneBill(const oneBill& bill);
    void removeOneBill(size_t index);
    void saveData_split()const;
    void readData_split();
    mainData database;
    map<QString, double> balances;
};

#endif // SPLITMANAGER_H
