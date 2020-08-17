#ifndef JSQLITE3_H
#define JSQLITE3_H

#include <QString>
#include <QStringList>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QSqlDatabase>
#include <QMap>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVariantList>
#include <QFileInfo>
class Jsqlite3
{
public:
    Jsqlite3();
    bool init(QString filename);
    bool AddData(QString table,QVariantList &values);//增
    bool UpData(QString table,QVariantList &values);//改
    bool DelData(QString table, QString index);//删
    bool NewDatatable(QString table,QStringList &formnames, QMap<QString, QString> &formstyle);//新建数据表
    bool runsql(QString sql, QList<QSqlRecord> &record);
    bool GetFormswish(QString table,QStringList formname,QMap<QString, QString> &wish,QList<QSqlRecord> &record);
    bool initnewsql();
    bool initaddsql();
    bool initdelsql(QString index);
    bool initupdatasql(QString index);
    bool initfindsql(QString index);
private:
    QList<QSqlRecord> recorddata;//筛选出来的数据集
    QSqlDatabase DatabaseName;//数据库实例
    QString ConnectName;//数据库连接实例的连接名称，以文件名区分连接实例
    QString DatafileName;//数据库文件的数据文件名，可能包含文件路径
    const QString tablename="data";//数据表名称，固定名称
    /////////////////////
    /// /数据表结构也固定文件形式为SQLite3数据库文件，后缀为“.j”大小写不敏感
    const QStringList formnames={"index","style","entry","contents","explain","comment"};
    const QStringList formstyle={"int","TEXT","TEXT","TEXT","TEXT","TEXT"};
    ////////////////////
    QString newtablesql;//新建数据表的sql语句
    QString adddatasql;//添加数据的sql语句
    QString deldatasql;//删除数据的sql语句
    QString updatasql;//更新数据的sql语句
    QString findsql;//查询数据的sql语句
    QString findallsql;//查询所有数据的sql语句
    QString findformssql;//查询特定数据项的sql语句
    QString findformswheresql;//查询符合特定值的数据项的sql语句
};

#endif // JSQLITE3_H
