#include "jrtclass.h"
JRTclass * JRTclass::m_pFirstclass=nullptr;
JuneObject *JRTclass::fCreateObject()
{
    if(m_pfCreateObject==nullptr)
    {
        qDebug()<<"JuneObject *JRTclass::fCreateObject";
        return nullptr;
    }

    JuneObject *pb=nullptr;
    pb=(*m_pfCreateObject)();
    return pb;
}

void JRTclass::fWriteJuneclass(QDataStream &data)
{
    data<<m_classname<<m_wschema;
}
 JRTclass * JRTclass::fReadJuneClass(QDataStream &data, QString pclassname)
{
    //mfc中增加了异步的同步操作算子来对多线程读写JRTclass形成的运行时刻类型识别链表，进行控制操作
     QString  classname;
     int wschema;

     JRTclass * pclass;

     data>>classname>>wschema;
     for(pclass=JRTclass::m_pFirstclass;pclass!=nullptr;pclass=pclass->m_pNextclass)
     {
         if(pclass->m_classname==pclassname&&pclass->m_classname==classname&&pclass->m_wschema==wschema)
             return pclass;
     }

     qDebug()<<"JRTclass * JRTclass::fReadJuneClass(JuneDataStream &data ,int m_wschema)";
     return nullptr;
}
