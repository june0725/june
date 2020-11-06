#ifndef JUNE_MAIN_H
#define JUNE_MAIN_H

#include <QMainWindow>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif

#include "jmdiarea.h"
#include "jtextedit.h"
#include "jdockwidgets.h"
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
public slots:
    void sactionfont(QString f);
    void sactionsize(QString s);
    void sactioncolor(QString c);
    ///////////////////
    void sactionadd();
    void sactionblack();
    void sactioncatalog();
    void sactioncenter();
    void sactioncodestyle();
    void sactionexam();
    void sactionexplain();
    void sactionform();
    void sactionfound();
    void sactionfream();
    void sactionguess();
    void sactionhelp();
    void sactionhtml();
    void sactionitalic();
    void sactionjust();
    void sactionleft();
    void sactionlist();
    void sactionlisten();
    void sactionnew();
    void sactionopen();
    void sactionpdf();
    void sactionpicture();
    void sactionplain();
    void sactionpreview();
    void sactionprint();
    void sactionprogress();
    void sactionread();
    void sactionright();
    void sactionsave();
    void sactionset();
    void sactionsetting();
    void sactionsort();
    void sactionsource();
    void sactionspeak();
    void sactionstyle();
    void sactiontab();
    void sactiontable();
    void sactiontest();
    void sactiontext();
    void sactionticket();
    void sactiontips();
    void sactionunder();
    void sactionwrite();


public:
    //tabwidget
   // JTab *tabedit;
    //mdi
    JMdiArea *mdiArea;
    //dock
    QList<JDockWidgets *>dock;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QComboBox *comboColor;
private:
        Ui::June_Main *ui;



};
#endif // JUNE_MAIN_H
