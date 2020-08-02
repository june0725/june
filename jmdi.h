#ifndef JMDI_H
#define JMDI_H


#include <QMdiArea>
#include <QMdiSubWindow>
#include <QWidgetList>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextEdit>
#include <QtDebug>




#include "jtab.h"
namespace Ui {
class JMdi;
}

class JMdi : public QMdiArea
{
    Q_OBJECT

public:
    explicit JMdi(QWidget *parent = nullptr);
    ~JMdi();

    bool AddeditChild(const QString f);
    bool AddmdiChild(QWidget *w);
    bool AddMainEdit(JTab *tabedit);
private:
    Ui::JMdi *ui;
    QTextEdit *textEdit;
};

#endif // JMDI_H
