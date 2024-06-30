#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <vector>
#include <map>
#include <QString>

using namespace std;

using Subcategories = vector<QString>;
using Categories = map<QString, Subcategories>;

class categoryManager {
public:
    categoryManager();

    void addCategory(const QString& category);

    void addSubcategory(const QString& category, const QString& subcategory);

    void removeCategory(const QString& category);

    void removeSubcategory(const QString& category, const QString& subcategory);

    static const Categories& getCategories();

private:
    static Categories categories;

    void initDefault();
};

#endif // CATEGORYMANAGER_H
