#include "jsqlite3.h"

Jsqlite3::Jsqlite3()
{


    formnames<<"id"<<"number"<<"style"<<"entry"<<"contents"<<"explain"<<"notes"<<"photo"<<"voice"<<"link";
    formstyle<<"int"<<"int"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT";
    for(int i=0;i<formnames.count();i++)
        formstyles.insert(formnames[i],formstyle[i]);
    tablename="data";
    datafilename="newjdatafile.j";
    for(int i=0;i<formnames.count();i++)
        formstyles.insert(formnames[i],formstyle[i]);

}



