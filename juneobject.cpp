#include "juneobject.h"
struct JRTclass JuneObject::JuneObjectclass={"JuneObjectclass",10,nullptr,nullptr,nullptr};
void JuneObject::Jinitclasslist(JRTclass *pnew)
{
    pnew->m_pNextclass=JRTclass::m_pFirstclass;
    JRTclass::m_pFirstclass=pnew;

}

JuneObject::JuneObject()
{
    Jinitclasslist(&JuneObject::JuneObjectclass);
    JuneObject::JuneObjectclass.m_pfCreateObject=&fCreatrObject;


}

void JuneObject::fSerialize(QDataStream &jdata, int f)
{
    if(f==1)
    {

    }

    if(f==2)
    {

    }
}

QDataStream & operator>>(QDataStream &jdata,const JuneObject *job)
{
    int dataflag=1;
    JRTclass *rd=JRTclass::fReadJuneClass(jdata,"JuneObjectclass");

    if(rd)
    {
        job=rd->fCreateObject();
    }else
    {qDebug()<<"QDataStream & operator>>(QDataStream &jdata,const JuneObject *job)/job=rd->fCreateObject()";}

    if(job)
    {
        ((JuneObject *)job)->fSerialize(jdata,dataflag);
    }else
    {qDebug()<<"QDataStream & operator>>(QDataStream &jdata,const JuneObject *job)/((JuneObject *)job)->fSerialize(jdata,dataflag)";}

    return jdata;
}

QDataStream & operator<<(QDataStream &jdata,const JuneObject *job)
{
   int dataflag=2;
    if(job)
    {
        JRTclass *jclass=job->GetJRTclass();
        jclass->fWriteJuneclass(jdata);
        ((JuneObject *)job)->fSerialize(jdata,dataflag);
    }else
    {qDebug()<<"QDataStream & operator<<(QDataStream &jdata,const JuneObject *job)/job";}

    return jdata;
}
