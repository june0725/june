#ifndef JUNEOBJECT_H
#define JUNEOBJECT_H

#include <QDataStream>


#include "jrtclass.h"

class JuneDataStream;
struct JRTclass;

class JuneObject
{
public:
    JuneObject();
    ////////////////
    static JRTclass JuneObjectclass;
    static JuneObject *fCreatrObject(){return new JuneObject;}
    virtual void fSerialize(QDataStream & jdata,int f);
    virtual JRTclass * GetJRTclass()const{return &JuneObject::JuneObjectclass;}
    static void Jinitclasslist(JRTclass *pnew);
    friend QDataStream & operator>>(QDataStream &jdata,const JuneObject *job);
    friend QDataStream & operator<<(QDataStream &jdata,const JuneObject *job);
};

#endif // JUNEOBJECT_H
