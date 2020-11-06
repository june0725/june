#ifndef JSQLITE3_H
#define JSQLITE3_H

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


class Jsqlite3
{

    /////////////////////
    ////数据表结构也固定文件形式为SQLite3数据库文件，后缀为“.j”大小写不敏感
    /// ////////////////////////
public:
    Jsqlite3();
    ~Jsqlite3();
    bool init(QString filename);
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
    bool DataBaseOpens();

    QSqlDatabase DatabaseName;//数据库实例
    QString DatafileName;//数据库文件的数据文件名，可能包含文件路径
    QMap<QString,QSQLite3_DataStruct> datatableist;//每个数据表对应的操作的sql语句类



};

#endif // JSQLITE3_H
