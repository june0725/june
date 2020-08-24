#ifndef JSQLITE3_H
#define JSQLITE3_H

#include "qsqlite3_database.h"

class Jsqlite3
{
public:
    Jsqlite3(QString filename);   
    bool AddData(QVariantList &values);//增
    bool UpData(QVariantList &values);//改
    bool DelData(QString index);//删
private:
    QList<QSqlRecord> recorddata;//筛选出来的数据集
    QSQLITE3_database DatabaseName;//数据库实例
    QString ConnectName;//数据库连接实例的连接名称，以文件名区分连接实例
    QString DatafileName;//数据库文件的数据文件名，可能包含文件路径

    /////////////////////
    /// /数据表结构也固定文件形式为SQLite3数据库文件，后缀为“.j”大小写不敏感
    QStringList formnames;
    QStringList formstyle;
    QString tablename;//数据表名称，固定名称
    QMap<QString,QString> formstyles;

};

#endif // JSQLITE3_H
