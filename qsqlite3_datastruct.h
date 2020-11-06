#ifndef QSQLITE3_DATASTRUCT_H
#define QSQLITE3_DATASTRUCT_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QDebug>



//数据表操作sql类，负责产生对应数据表的各个操作sql语句
class QSQLite3_DataStruct
{
public:
    QSQLite3_DataStruct();
    ~QSQLite3_DataStruct();
    bool init(QString tab,QStringList &formnames, QMap<QString, QString> &formstyle);
    bool initnewsql();
    bool initaddsql();
    bool initdelsql(QString index);
    bool initupdatasql(QString index);
    bool initfindsql(QString index);
    bool initfindallsql();
    bool initfindformssql(QStringList formname);
    bool initfindformswheresql(QStringList formname,QMap<QString, QString> &wish);
    QString tablename;//数据表名称
    QStringList form;//数据表项集合，具有顺序性。
    QMap<QString,QString> formlist;//对应数据项名称和对应的类型（是字符类型的说明，无序的（键-值）集合）
    QString newtablesql;//新建数据表的sql语句
    QString adddatasql;//添加数据的sql语句
    QString deldatasql;//删除数据的sql语句
    QString updatasql;//更新数据的sql语句
    QString findsql;//查询数据的sql语句
    QString findallsql;//查询所有数据的sql语句
    QString findformssql;//查询特定数据项的sql语句
    QString findformswheresql;//查询符合特定值的数据项的sql语句
};

#endif // QSQLITE3_DATASTRUCT_H
