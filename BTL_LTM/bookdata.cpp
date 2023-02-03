#include "bookdata.h"
#include "ui_bookdata.h"
#include <xlsxdocument.h>
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include <QMessageBox>
bookdata::bookdata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bookdata)
{
    ui->setupUi(this);
    setWindowTitle("Book loan data");
    //------------laod table--------------------
    staff FBconn;
    QSqlQueryModel *model= new QSqlQueryModel ();
    FBconn.connect();
    QSqlQuery *queryload = new QSqlQuery(FBconn.getdata());
    QString view = "SELECT * FROM Borrowbook " ;
    queryload->prepare(view);
    queryload->exec();
    model->setQuery(*queryload);
    ui->tableView->setModel(model);
    FBconn.Disconnect();
}
bookdata::~bookdata()
{
    delete ui;
}
void bookdata::on_btnfind_clicked()
{
    staff conn;
    QString username = ui->txtusername->text();
    QString book=ui->txtbook->text();
    QString date=ui->txtdate->text();
    if(username==NULL && book==NULL && date==NULL) {

        QSqlQueryModel *model= new QSqlQueryModel ();
        conn.connect();
        QSqlQuery *queryload = new QSqlQuery(conn.getdata());
        QString view = "SELECT * FROM Borrowbook " ;
        queryload->prepare(view);
        queryload->exec();
        model->setQuery(*queryload);
        ui->tableView->setModel(model);
        conn.Disconnect();
    }
    else {
        QSqlQueryModel *model= new QSqlQueryModel ();
        conn.connect();
        QSqlQuery *queryload = new QSqlQuery(conn.getdata());
        QString view = "SELECT * From Borrowbook WHERE username='"+username+"' or book='"+book+"' or date='"+date+"'  ";
        queryload->prepare(view);
        queryload->exec();
        model->setQuery(*queryload);
        ui->tableView->setModel(model);
        conn.Disconnect();

    }


}

void bookdata::on_btnExcel_clicked()
{
    staff conn;
    if(!conn.connect()){
        qDebug() <<"Failed to open the database";
        return;
    }
    conn.connect();
    QSqlQuery qry;

    qry.prepare("select * from Borrowbook");
    qDebug()<<qry.executedQuery();

    QXlsx::Document xlsx;
    QXlsx::Format format1;/*Set the style of the unit*/
       format1.setFontColor(QColor(Qt::blue));/*Text is blue*/
       format1.setFontSize(13);/*Set font size*/
       format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*Horizontal centering*/
       format1.setBorderStyle(QXlsx::Format::BorderDashDotDot);/*Border style*/


    xlsx.write(1, 1, "username",format1);
    xlsx.write(1, 2, "book",format1);
    xlsx.write(1, 3, "date",format1);
    if(qry.exec()) {
        int k = 2;
    while(qry.next()){
        xlsx.write(k,1,qry.value(0).toString());
        xlsx.write(k,2,qry.value(1).toString());
        xlsx.write(k,3,qry.value(2).toString());

    k++;

        } conn.Disconnect();
     }
        xlsx.saveAs("C:/Users/PV/Documents/B19DCCN424_TranNguyenManh_BC3/libManager/qlbookborrow.xlsx");

        qDebug()<<"Export to excel success";
}

