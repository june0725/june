#ifndef JMDIAREA_H
#define JMDIAREA_H

#include <QMdiArea>
#include <QList>
#include <QMdiSubWindow>
#include <QWidgetList>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextEdit>
#include <QtDebug>

#include "jtextedit.h"
class JMdiArea: public QMdiArea
{
    Q_OBJECT
public:
   explicit JMdiArea(QWidget *parent = nullptr);
    ~JMdiArea();
    JTextEdit *Addchildren(QString n);
    JTextEdit *Getactiveedit();


};

#endif // JMDIAREA_H
