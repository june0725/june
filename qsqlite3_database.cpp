#include "qsqlite3_database.h"



QSQLITE3_database::QSQLITE3_database()
{


}
bool QSQLITE3_database::init(QString filename)
{
    QStringList forms;//数据表数据项
    QMap<QString,QString> formtypelist;//数据表项对应的数据类型

    ConnectName=filename;
    DatafileName=filename;

    DataBaseOpens();
    GetTableList(tables);
    for(int i=0;i<tables.count();i++)
    {
      GetFormList(tables[i],forms);
      GetformtypeList(tables[i],formtypelist);
      datatableist.insert(tables[i],QSQLite3_DataStruct());
      datatableist[tables[i]].init(tables[i],forms,formtypelist);
      forms.clear();
      formtypelist.clear();

    }

    return true;
}
bool QSQLITE3_database::NewDatatable(QString table, QStringList &formnames, QMap<QString, QString> &formstyle)
{
    tables<<table;
    datatableist.insert(table,QSQLite3_DataStruct());
    datatableist[table].init(table,formnames,formstyle);
    datatableist[table].initnewsql();
    if (DatabaseName.open())
    {
        QSqlQuery query(DatabaseName);
        query.prepare(datatableist[table].newtablesql);

        if (!query.exec()) {
            qDebug()<<"database new data table failt"<<Qt::endl<<query.lastError();
            return false;
        }
        query.finish();
    }

return true;
}
bool QSQLITE3_database::DelData(QString table, QString index)
{
    datatableist[table].initdelsql(index);
     if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].deldatasql);

            if (!query.exec())
            {
                qDebug()<<"database delete data failt"<<Qt::endl<<query.lastError();
                return false;
            }
            query.finish();
        }

        return true;
}
bool QSQLITE3_database::GetindexData(QString table, QString index,QList<QSqlRecord> &record)
{
    datatableist[table].initfindsql(index);
     if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].findsql);

            if (!query.exec())
            {
                qDebug()<<"database GetindexData failt"<<Qt::endl<<query.lastError();
                return false;
            }
            while (query.next())
            {
                record.append(query.record());
            }
            query.finish();
        }

        return true;
}
bool QSQLITE3_database::GetData(QString table,QMap<QString ,QString> &findvalue,QList<QSqlRecord> &record)
{
    datatableist[table].initfindallsql();
     if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].findallsql);

            if (!query.exec())
            {
                qDebug()<<"database GetData findvalue failt"<<Qt::endl<<query.lastError();
                return false;
            }
            while (query.next())
            {
                for (QMap<QString,QString>::const_iterator i=findvalue.constBegin();i!=findvalue.constEnd();i++ )
                {
                    QSqlRecord a=query.record();
                    if(a.contains(i.key())&&a.value(i.key())==i.value())
                    {
                        record.append(a);
                    }

                }

            }
            query.finish();
        }

        return true;
}
bool QSQLITE3_database::GetallData(QString table,QList<QSqlRecord> &record)
{
    datatableist[table].initfindallsql();
     if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].findallsql);

            if (!query.exec())
            {
                qDebug()<<"database GetallData failt"<<Qt::endl<<query.lastError();
                return false;
            }
            while (query.next())
            {
                QSqlRecord a=query.record();
                record.append(a);
            }
            query.finish();
        }

        return true;
}
bool QSQLITE3_database::GetFormData(QString table,QStringList formname,QList<QSqlRecord> &record)
{
    datatableist[table].initfindformssql(formname);
     if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].findformssql);

            if (!query.exec())
            {
                qDebug()<<"database GetFormData failt"<<Qt::endl<<query.lastError();
                return false;
            }
            while (query.next())
            {
                QSqlRecord a=query.record();
                record.append(a);
            }
            query.finish();
        }

        return true;
}
bool QSQLITE3_database::GetFormswish(QString table,QStringList formname,QMap<QString, QString> &wish,QList<QSqlRecord> &record)
{
    datatableist[table].initfindformswheresql(formname,wish);
     if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].findformswheresql);

            if (!query.exec())
            {
                qDebug()<<"database GetFormswish failt"<<Qt::endl<<query.lastError();
                return false;
            }
            while (query.next())
            {
                QSqlRecord a=query.record();
                record.append(a);
            }
            query.finish();
        }

        return true;
}
bool QSQLITE3_database::UpData(QString table, QVariantList &values)
{
    datatableist[table].initupdatasql(values[0].toString());
    if(datatableist[table].form.count()!=values.count())
    {
        qDebug()<<"updata data failt"<<Qt::endl
               <<"don't have same count number"<<Qt::endl;
        return false;
    }

        if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].updatasql);
            for(int i=0;i<datatableist[table].form.count();i++)
            {
                query.bindValue(":"+datatableist[table].form[i],values[i]);
            }
            if (!query.exec())
            {
                qDebug()<<"database updata failt"<<Qt::endl<<query.lastError();
                return false;
            }
            query.finish();
        }

        return true;
}
bool QSQLITE3_database::AddData(QString table, QVariantList &values)
{

    datatableist[table].initaddsql();
    if(datatableist[table].form.count()!=values.count())
    {
        qDebug()<<"add data failt"<<Qt::endl
               <<"don't have same count number"<<Qt::endl;
        return false;
    }

        if (DatabaseName.open())
        {
            QSqlQuery query(DatabaseName);
            query.prepare(datatableist[table].adddatasql);
            for(int i=0;i<datatableist[table].form.count();i++)
            {
                query.bindValue(":"+datatableist[table].form[i],values[i]);
            }

            if (!query.exec()) {
                qDebug()<<"database adddata failt"<<Qt::endl<<query.lastError();
                return false;
            }
            query.finish();
        }

    return true;
}
bool QSQLITE3_database::DataBaseOpens()
{
    //与数据库建立连接
    if (QSqlDatabase::contains(ConnectName))
    {
        DatabaseName = QSqlDatabase::database(ConnectName);
    }
    else
    {
        DatabaseName = QSqlDatabase::addDatabase("QSQLITE", ConnectName);
    }

    DatabaseName.setDatabaseName(ConnectName);
    //打开数据库
    if (!DatabaseName.open())
    {
        qDebug()<<"database init failt"<<Qt::endl
               <<"database don't open"<<Qt::endl;
        return false;
    }

    return true;
}
QSQLITE3_database::~QSQLITE3_database()
{
    if (DatabaseName.open())
            DatabaseName.close();
}
bool QSQLITE3_database::GetFormList(QString formname, QStringList &formlist)
{
    QSqlRecord rc;
    if (!DatabaseName.open())
    {        
        qDebug()<<"GetFormList failt"<<Qt::endl
               <<"database don't open"<<Qt::endl;
        return false;
    }

    rc=DatabaseName.record(formname);
    if(rc.isEmpty())
    {
        qDebug()<<"QSqlRecord  is empty"<<Qt::endl;
        return  false;
    }

    for(int i=0;i<rc.count();i++)
          formlist.insert(i,rc.fieldName(i));

    return true;

}
bool QSQLITE3_database::GetTableList(QStringList &tablelist)
{
    if (!DatabaseName.open())
    {
        qDebug()<<"GetTableList failt"<<Qt::endl
               <<"database don't open"<<Qt::endl;
    }

    tablelist=DatabaseName.tables();

    if(tablelist.isEmpty())
    {
        qDebug()<<"GetTableList tablelist is empty"<<Qt::endl;
        return false;
    }


    return true;
}
bool QSQLITE3_database::GetformtypeList(QString formname, QMap<QString, QString> &indexlist)
{
    QSqlRecord rc;
    if (!DatabaseName.open())
    {
        qDebug()<<"GetformtypeList failt"<<Qt::endl
               <<"database don't open"<<Qt::endl;
    }

    rc=DatabaseName.record(formname);

    if(rc.isEmpty())
    {
        qDebug()<<"GetformtypeList QSqlRecord  is empty"<<Qt::endl;
        return  false;
    }

        for(int i=0;i<rc.count();i++)
              indexlist[rc.fieldName(i)]=rc.value(i).typeName();



    return true;
}
bool QSQLITE3_database::Newdatafile(QString filename,QString table,QStringList &formnames, QMap<QString, QString> &formstyle)
{
   init(filename);
   if(!NewDatatable(table,formnames,formstyle))
           return false;

    return true;
}
bool QSQLITE3_database::runsql(QString sql,QList<QSqlRecord> &record)
{
    if (DatabaseName.open())
       {
           QSqlQuery query(DatabaseName);
           query.prepare(sql);

           if (!query.exec())
           {
               qDebug()<<"runsql database GetData failt"<<Qt::endl<<query.lastError();
               return false;
           }
           while (query.next())
           {
             record.append(query.record());
           }

            query.finish();
        }
    return true;
}
