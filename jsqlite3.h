#ifndef JSQLITE3_H
#define JSQLITE3_H

#include "qsqlite3_database.h"
#include "treeitem.h"

class Jsqlite3
{

    /////////////////////
    ////数据表结构也固定文件形式为SQLite3数据库文件，后缀为“.j”大小写不敏感
    /// ////////////////////////
public:
    Jsqlite3();

    /////返回一个目录
     bool getdeeptree(QString data,QStringList &l);
    /////返回一个记录集
     bool getwidetree(QString data,QList<QSqlRecord> &r);

    void open_jfile(QString filename);
    void save_jfile(QString filename);
    QList<QSqlRecord> recorddata;//筛选出来的数据集
    QSQLITE3_database DatabaseName;//数据库实例

    QStringList formnames;
    QStringList formstyle;
    QString tablename;//数据表名称，固定名称
    QMap<QString,QString> formstyles;
    QString datafilename;


};

#endif // JSQLITE3_H
