#ifndef JUNE_MAIN_H
#define JUNE_MAIN_H

#include <QMainWindow>
#include <QAction>
#include <QCloseEvent>
#include <QMenu>
#include <QMap>
#include <QPointer>
#include <QDate>
#include <QDockWidget>
#include <QListWidget>

#include "jmdi.h"
#include "jtab.h"
#include "jdockwidget.h"
#include "sqlitedata.h"
#include "j_word.h"


QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;

namespace Ui { class June_Main; }
QT_END_NAMESPACE

class June_Main : public QMainWindow
{
    Q_OBJECT

public:
    June_Main(QWidget *parent = nullptr);
    ~June_Main();    

    //tabwidget
    JTab *tabedit;
    //mdi
    JMdi *mdiArea;
    //dock
    QList<JDockWidget *>dock;

private:
        Ui::June_Main *ui;



};
#endif // JUNE_MAIN_H
