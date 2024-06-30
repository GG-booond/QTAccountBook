#ifndef QUANJU_H
#define QUANJU_H
#include <mainData.h>
#include<QCheckBox>
#include"splitManager.h"
#include "categoryManager.h"
#define sumALLplans "总计划数目"

class quanju
{
public:
    quanju();
};
extern mainData myData;
extern QString back;
extern splitManager splitt;
//extern categoryManager myCate;
extern QMap<QString, double> plans; // 用于存储类别和对应的数字
#endif // QUANJU_H
