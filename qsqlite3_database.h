#ifndef QSQLITE3_DATABASE_H
#define QSQLITE3_DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMap>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVariantList>
#include <QFileInfo>

#include "qsqlite3_datastruct.h"




//数据库操作类，只对应sqlite3类型,目前不能增加数据表的项目，可以新建数据表
class QSQLITE3_database
{

public:
    explicit QSQLITE3_database();
    ~QSQLITE3_database();
    bool init(QString filename);
    QString GetDatafilename(){return DatafileName;}
    QSqlDatabase GetSQLdatabase(){return DatabaseName;}
    bool Newdatafile(QString filename,QString table,QStringList &formnames, QMap<QString, QString> &formstyle);
    /////////////////////////////////////
    bool GetFormList(QString formname,QStringList &formlist);
    bool GetTableList(QStringList &tablelist);
    bool GetformtypeList(QString formname,QMap<QString,QString> &indexlist);
    /////////////////////////////////////////////
    bool AddData(QString table,QVariantList &values);//增
    bool UpData(QString table,QVariantList &values);//改
    bool DelData(QString table, QString index);//删
    bool NewDatatable(QString table,QStringList &formnames, QMap<QString, QString> &formstyle);//新建数据表
    //查询包含特定的值的数据，可以查找某一个字段或值的数据
    bool GetData(QString table,QMap<QString ,QString> &findvalue,QList<QSqlRecord> &record);
    //主键默认为第一个，带索引和计数性质的主键，索引一个数据表项
    bool GetindexData(QString table, QString index,QList<QSqlRecord> &record);
    //查询所有数据项和数据值
    bool GetallData(QString table,QList<QSqlRecord> &record);
    //查找某一项目的数据
    bool GetFormData(QString table,QStringList formname,QList<QSqlRecord> &record);
    bool GetFormswish(QString table,QStringList formname,QMap<QString, QString> &wish,QList<QSqlRecord> &record);
    bool runsql(QString sql, QList<QSqlRecord> &record);
private:
    bool DataBaseOpens();


    QSqlDatabase DatabaseName;//数据库实例
    QString ConnectName;//数据库连接实例的连接名称，以文件名区分连接实例
    QString DatafileName;//数据库文件的数据文件名，可能包含文件路径

    QStringList tables;//数据表名称
    QMap<QString,QSQLite3_DataStruct> datatableist;//每个数据表对应的操作的sql语句类



};

#endif // QSQLITE3_DATABASE_H
