#ifndef BOOKDATA_H
#define BOOKDATA_H

#include <QWidget>
#include <QTableWidget>
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableView>
#include"staff.h"

namespace Ui {
class bookdata;
}

class bookdata : public QWidget
{
    Q_OBJECT

public:
    explicit bookdata(QWidget *parent = 0);
    ~bookdata();

private slots:
    void on_btnfind_clicked();
private slots:
    void on_btnExcel_clicked();

private:
    Ui::bookdata *ui;
};

#endif // BOOKDATA_H
