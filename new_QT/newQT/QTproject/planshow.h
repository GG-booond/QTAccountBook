#ifndef PLANSHOW_H
#define PLANSHOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class planShow; }
QT_END_NAMESPACE

class planShow : public QWidget
{
    Q_OBJECT

public:
    planShow(QWidget *parent = nullptr);
    ~planShow();

private slots:
    void on_buttonEditPlan_clicked();

private:
    Ui::planShow *ui;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *dateLayout; // 添加日期布局的声明
    QDateEdit *dateEdit; // 添加日期编辑器的声明

    void loadPlansFromFile();
};

#endif // PLANSHOW_H
