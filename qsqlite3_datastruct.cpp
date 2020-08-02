#include "qsqlite3_datastruct.h"


QSQLite3_DataStruct::QSQLite3_DataStruct()
{

}
bool QSQLite3_DataStruct::init(QString tab,QStringList &formnames, QMap<QString, QString> &formstyle)
{

    tablename=tab;
    form=formnames;
    formlist=formstyle;
    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty())
    {
        qDebug()<<"formlist is empty!";
        return false;
    }

    return true;
}
QSQLite3_DataStruct::~QSQLite3_DataStruct()
{

}
bool QSQLite3_DataStruct::initnewsql()
{
    //新建数据表
    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty())
    {
        qDebug()<<"formlist is empty!";
        return false;
    }

    int first=0;

    newtablesql="CREATE TABLE '"+tablename+"' ('"+form[first]+"' "+formlist[form[first]]+" NOT NULL PRIMARY KEY UNIQUE,";
    for(first=1;first<form.count()-1;first++)
    {
        newtablesql=newtablesql+"'"+form[first]+"' "+formlist[form[first]]+",";
    }
    first=form.count()-1;
    newtablesql=newtablesql+"'"+form[first]+"' "+formlist[form[first]]+")";



    return true;

}
bool QSQLite3_DataStruct::initaddsql()
{
    //插入数据
    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty())
    {
        qDebug()<<"formlist is empty!";
        return false;
    }

    int first=0;
    QString a;
    QString b;

    for(first=0;first<form.count()-1;first++)
    {
        a=a+form[first]+",";
        b=b+":"+form[first]+",";
    }
    first=form.count()-1;
    a=a+form[first];
    b=b+":"+form[first];
    adddatasql="INSERT INTO "+tablename+"("+a+") VALUES ("+b+")";


    return true;
}
bool QSQLite3_DataStruct::initupdatasql(QString index)
{
    //更新数据
    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty())
    {
        qDebug()<<"formlist is empty!";
        return false;
    }

    int first=0;
    updatasql="UPDATE "+tablename+" SET ";
    for(first=1;first<form.count()-1;first++)
    {
        updatasql=updatasql+form[first]+" = "+":"+form[first]+",";
    }
    first=form.count()-1;
    updatasql=updatasql+form[first]+" = "+":"+form[first]+" WHERE "+form[0]+" = "+index;


    return true;
}
bool QSQLite3_DataStruct::initdelsql(QString index)
{
    //删除数据
    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty())
    {
        qDebug()<<"formlist is empty!";
        return false;
    }

   deldatasql="DELETE FROM "+tablename+" WHERE "+form[0]+" = "+index;

    return true;
}
bool QSQLite3_DataStruct::initfindsql(QString index)
{
    //查询数据
    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty())
    {
        qDebug()<<"formlist is empty!";
        return false;
    }

   findsql="SELECT * FROM "+tablename+" WHERE "+form[0]+" = "+index;

    return true;
}
bool QSQLite3_DataStruct::initfindallsql()
{
    //查询数据
    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty())
    {
        qDebug()<<"formlist is empty!";
        return false;
    }

   findallsql="SELECT * FROM "+tablename;

    return true;
}
bool QSQLite3_DataStruct::initfindformssql(QStringList formname)
{
    //查询数据

    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty()|formname.isEmpty())
    {
        qDebug()<<"form is empty!";
        return false;
    }
    int first=0;
    QString a;
    for(first=0;first<formname.count()-1;first++)
    {
        if(form.contains(formname[first]))
           a=a+formname[first]+", ";
    }

    first=formname.count()-1;
    if(form.contains(formname[first]))
         a=a+formname[first];

   findformssql="SELECT "+a+" FROM "+tablename;

    return true;
}
bool QSQLite3_DataStruct::initfindformswheresql(QStringList formname,QMap<QString, QString> &wish)
{
    //查询数据

    if(formlist.isEmpty()|tablename.isEmpty()|form.isEmpty()|formname.isEmpty())
    {
        qDebug()<<"form is empty!";
        return false;
    }
    int first=0;
    QString a;
    for(first=0;first<formname.count()-1;first++)
    {
        if(form.contains(formname[first]))
           a=a+formname[first]+", ";
    }

    first=formname.count()-1;
    if(form.contains(formname[first]))
         a=a+formname[first];
    if(wish.count()==1)
    {
        findformswheresql="SELECT "+a+" FROM "+tablename+" WHERE "+wish.firstKey()+" = \""+wish[wish.firstKey()]+"\"";
    }
    else
    {
        first=0;
        QString b;
        QMap<QString, QString>::const_iterator i = wish.constBegin();
        while (i != wish.constEnd()-1) {
            if(form.contains(i.key()))
               b=b+i.key()+" = \""+i.value()+"\" AND ";
            ++i;
            }

            i=wish.constEnd()-1;
        if(form.contains(i.key()))
           b=b+i.key()+" = \""+i.value()+"\"";

//        for(first=0;first<form.count()-1;first++)
//        {
//            if(wish.contains(form[first]))
//               b=b+form[first]+" = \""+wish[form[first]]+"\" AND ";
//        }

//        first=form.count()-1;
//        if(wish.contains(form[first]))
//           b=b+form[first]+" = \""+wish[form[first]]+"\"";
        findformswheresql="SELECT "+a+" FROM "+tablename+" WHERE "+b;
    }


    return true;
}
