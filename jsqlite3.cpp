#include "jsqlite3.h"

Jsqlite3::Jsqlite3(QString filename)
{
    formnames<<"id"<<"style"<<"entry"<<"contents"<<"explain"<<"notes"<<"photo"<<"voice"<<"link";
    formstyle<<"int"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT";
    for(int i=0;i<formnames.count();i++)
        formstyles.insert(formnames[i],formstyle[i]);
    tablename="data";
    for(int i=0;i<formnames.count();i++)
        formstyles.insert(formnames[i],formstyle[i]);
    ConnectName=filename;
    DatafileName=filename;

    if(!QFile::exists(filename))
        DatabaseName.Newdatafile(filename,tablename,formnames,formstyles);
    DatabaseName.init(filename);


}

bool Jsqlite3::DelData(QString index)
{
    DatabaseName.DelData(tablename,index);
        return true;
}
bool Jsqlite3::UpData(QVariantList &values)
{
    DatabaseName.UpData(tablename,values);

        return true;
}
bool Jsqlite3::AddData(QVariantList &values)
{
    DatabaseName.AddData(tablename,values);

    return true;
}
