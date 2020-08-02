#include "sqlitedata.h"
#include "ui_sqlitedata.h"

SQLiteData::SQLiteData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SQLiteData)
{
    ui->setupUi(this);
    openmaindb();
}

SQLiteData::~SQLiteData()
{

    if (!maindatafile)
        delete maindatafile;
    if (!tabledata)
        delete tabledata;
    if (!dataview)
        delete dataview;
    delete ui;
}

void SQLiteData::openmaindb()
{

    maindatafile=new QSQLITE3_database();
    maindatafile->init(maindb);
    ui->tabWidget->setCurrentIndex(0);
    QList<QSqlRecord>rd;
    maindatafile->runsql(getfilenamesql,rd);

    int counter =ui->filelists->count();
       for(int index=0;index<counter;index++)
       {
           QListWidgetItem *item = ui->filelists->takeItem(index);
               delete item;
       }
       ui->filelists->clear();
    for (int i=0;i<rd.count();i++ )
    {
         ui->filelists->addItem(rd[i].value(0).toString());
    }

    ui->filelists->setCurrentRow(0);

    QString filename=ui->filelists->currentItem()->text();
     QMap<QString,QString> f;
     f["filename"]=filename;
     QList<QSqlRecord>rds;
     QStringList t;
     t<<"tablename";
     maindatafile->GetFormswish(maintable,t,f,rds);

     int counters =ui->tablelists->count();
        for(int index=0;index<counters;index++)
        {
            QListWidgetItem *item = ui->tablelists->takeItem(index);
                delete item;
        }
        ui->tablelists->clear();
     for (int i=0;i<rds.count();i++ )
     {
          ui->tablelists->addItem(rds[i].value(0).toString());
     }

     ui->tablelists->setCurrentRow(0);
}

void SQLiteData::Getopendata()
{
    choosefilename=ui->filelists->currentItem()->text();
    choosetablename=ui->tablelists->currentItem()->text();
    QMap<QString,QString> f;
    f["filename"]=choosefilename;
    f["tablename"]=choosetablename;
    QList<QSqlRecord>rd;
    QStringList t;
    t<<"style";
    maindatafile->GetFormswish(maintable,t,f,rd);
    choosestyle=rd[0].value(0).toString();
}

void SQLiteData::Viewchoosedata()
{
    ui->tabWidget->setCurrentIndex(1);
    choosefilename=ui->filelists->currentItem()->text();
    choosetablename=ui->tablelists->currentItem()->text();
    QMap<QString,QString> f;
    f["filename"]=choosefilename;
    f["tablename"]=choosetablename;
    QList<QSqlRecord>rd;
    QStringList t;
    t<<"style";
    maindatafile->GetFormswish(maintable,t,f,rd);
    choosestyle=rd[0].value(0).toString();
    if (!tabledata)
        delete tabledata;
    tabledata=new QSQLITE3_database();
    tabledata->init(choosefilename);
    dataview=new QSqlTableModel(this, tabledata->GetSQLdatabase());
    dataview->setTable(choosetablename);
    dataview->setEditStrategy(QSqlTableModel::OnManualSubmit);
    dataview->select();

    ui->dataviews->setModel(dataview);
    ui->dataviews->show();
    return;
}
void SQLiteData::viewfiles(QListWidgetItem *it)
{
    QString listwidgetname=it->listWidget()->objectName();

            if(listwidgetname=="filelists")
                {                    
                   QString filename=ui->filelists->currentItem()->text();
                    QMap<QString,QString> f;
                    f["filename"]=filename;
                    QList<QSqlRecord>rd;
                    QStringList t;
                    t<<"tablename";
                    maindatafile->GetFormswish(maintable,t,f,rd);

                    int counter =ui->tablelists->count();
                       for(int index=0;index<counter;index++)
                       {
                           QListWidgetItem *item = ui->tablelists->takeItem(index);
                               delete item;
                       }
                       ui->tablelists->clear();
                    for (int i=0;i<rd.count();i++ )
                    {
                         ui->tablelists->addItem(rd[i].value(0).toString());
                    }
                    ui->tablelists->setCurrentRow(0);
                    return;
                }
            if(listwidgetname=="tablelists")
                {
                    Getopendata();
                    return;
                }

}

