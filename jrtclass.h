#ifndef JRTCLASS_H
#define JRTCLASS_H

#include <QString>
#include <QDebug>
#include <QDataStream>

#include "juneobject.h"



#define JuneObjectWschema 10


class JuneObject;
class JuneDataStream;
struct JRTclass
{
public:
    QString m_classname;
    int m_wschema;    
    JRTclass *m_baseclass;
    static JRTclass *m_pFirstclass;
    JRTclass * m_pNextclass;
    JuneObject * (*m_pfCreateObject)();

    JuneObject *fCreateObject();
    void fWriteJuneclass(QDataStream &data);
    static JRTclass * fReadJuneClass(QDataStream &data,QString pclassname );
};

#endif // JRTCLASS_H
