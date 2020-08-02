#ifndef SQLITEDATA_H
#define SQLITEDATA_H

#include <QDialog>
#include <QListWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>

#include "qsqlite3_database.h"
////
///main.db
///maintable:id,style,filename,tablename,formname,formstyle
///
///
///
///
///
///
namespace Ui {
class SQLiteData;
}


class SQLiteData : public QDialog
{
    Q_OBJECT

public:
    explicit SQLiteData(QWidget *parent = nullptr);
    ~SQLiteData();

QString choosestyle;
QString choosefilename;
QString choosetablename;
public slots:
    void viewfiles(QListWidgetItem*it);
    void Getopendata();
    void Viewchoosedata();
private:   
    void openmaindb();
    QString maindb="main.db";
    QString maintable="maintable";
    QString getfilenamesql="SELECT DISTINCT filename FROM maintable";
    Ui::SQLiteData *ui;    
    QSQLITE3_database *maindatafile;
    QSQLITE3_database *tabledata;
    QSqlTableModel *dataview;
};

#endif // SQLITEDATA_H
