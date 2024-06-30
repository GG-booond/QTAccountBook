#ifndef PLANNING_H
#define PLANNING_H

#include <QWidget>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class planning; }
QT_END_NAMESPACE

class planning : public QWidget
{
    Q_OBJECT

public:
    explicit planning(QWidget *parent = nullptr);
    ~planning();
    void saveDateToFile();

private slots:
    //void on_buttonSavePlan_clicked();
    void loadPlansFromFile();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::planning *ui;

};

#endif // PLANNING_H
