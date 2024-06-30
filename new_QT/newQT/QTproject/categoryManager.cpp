#include "categoryManager.h"
#include "mainData.h"
#include <algorithm>
#include <vector>
#include <map>
#include <QString>
#include <QDebug>
#include <QFile>

using namespace std;

categoryManager::categoryManager() {
    initDefault();
}

void categoryManager::addCategory(const QString& category) {
    //qDebug() << category;
    //qDebug() << 1;
    if (categories.find(category) == categories.end()) {
        categories[category] = Subcategories();
        QFile file("/new_QT/newQT/QTproject/words/cusCate.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << category << "\n";
            file.close();
            qDebug() << "新大类已追加到文件";
        } else {
            qDebug() << "无法打开文件进行追加写入";
        }
        for (mainData* tmpDataObj : mainData::allMainDatas) {
            tmpDataObj->updateCateTotalAmounts(category, 0);
        } //给所有mainData对象的新category的sum初始化
    }
    else {
        //qDebug() << "不能添加已有的用途"; //应弹出警告对话框
    }
}

void categoryManager::addSubcategory(const QString& category, const QString& subcategory) {
    bool flag = true;
    for (size_t i = 0; i < categories[category].size(); ++i)
        if (categories[category][i] == subcategory) {
            //qDebug() << "不能添加已有的用途"; //应弹出警告对话框
            flag = false;
            break;
        }
    if (flag)
        categories[category].push_back(subcategory);
}

void categoryManager::removeCategory(const QString& category) {
    auto it = categories.find(category);
    if (it != categories.end())
        categories.erase(it);
    else
        qDebug() << "试图删除不存在的用途";
}

void categoryManager::removeSubcategory(const QString& category, const QString& subcategory) {
    auto it = categories.find(category);
    if (it != categories.end()) {
        auto& subcategories = it->second;
        subcategories.erase(remove(subcategories.begin(), subcategories.end(), subcategory), subcategories.end());
    }
    else
        qDebug() << "试图删除不存在的用途";
}

const Categories& categoryManager::getCategories() {
    return categories;
}

void categoryManager::initDefault() {
    addCategory("饮食");
    addSubcategory("饮食", "正餐");
    addSubcategory("饮食", "零食、饮料");
    addSubcategory("饮食", "水果");
    addSubcategory("饮食", "其它");

    addCategory("起居");
    addSubcategory("起居", "衣物");
    addSubcategory("起居", "鞋");
    addSubcategory("起居", "饰品");
    addSubcategory("起居", "美容、美发");
    addSubcategory("起居", "卫生用品");
    addSubcategory("起居", "水电、洗衣");
    addSubcategory("起居", "医疗");
    addSubcategory("起居", "其它");

    addCategory("学业");
    addSubcategory("学业", "文具");
    addSubcategory("学业", "读物");
    addSubcategory("学业", "资源");
    addSubcategory("学业", "学费");
    addSubcategory("学业", "报名费");
    addSubcategory("学业", "其它");

    addCategory("通勤");
    addSubcategory("通勤", "公共交通");
    addSubcategory("通勤", "共享车");
    addSubcategory("通勤", "出租车");
    addSubcategory("通勤", "火车票");
    addSubcategory("通勤", "船票");
    addSubcategory("通勤", "机票");
    addSubcategory("通勤", "其它");

    addCategory("娱乐");
    addSubcategory("娱乐", "礼物");
    addSubcategory("娱乐", "门票、入场券");
    addSubcategory("娱乐", "玩物");
    addSubcategory("娱乐", "数码");
    addSubcategory("娱乐", "其它");

    addCategory("其它");
    addSubcategory("其它", "其它");
    QFile ffile("/new_QT/newQT/QTproject/words/cusCate.txt");
    if (ffile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&ffile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            addCategory(line);
            addSubcategory(line, "其它");
        }
        ffile.close();
        qDebug() << "新大类已写入";
    } else {
        qDebug() << "无法打开文件进行读取";
    }
}

Categories categoryManager::categories;
