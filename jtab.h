#ifndef JTAB_H
#define JTAB_H

#include <QTabWidget>
#include <QWidgetList>
#include <QAction>
#include <QClipboard>
#include <QColorDialog>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QTextCodec>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QToolBar>
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
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

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QMenuBar;
class QPrinter;
QT_END_NAMESPACE

const QString rsrcPath = ":/images/win";


namespace Ui {
class JTab;

}
//管理类
class JTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit JTab(QWidget *parent = nullptr);
    ~JTab();
    void addtabwidget(QWidget *w,QString f);
    bool addtabeditfile(QString f);
    void addmainedit(QTextEdit *w);
    bool removeeditfile(QWidget *w);
    bool fOpenfile(QTextEdit *w,QString f);
    bool fMaybesave(QWidget *w,QString f);
    bool fSavefile(QWidget *w,QString f);
public slots:
    void CloseChild(int i);    
    void DbleClick(int i);
    void changeindex(int i);
    QWidget * fGetWidget(QString f);
    int fCheckname(QString f);
signals:
    void addmdi(QString fn);
    void closedfile(QString v,QString f);
private:
    Ui::JTab *ui;    
    QMap<QString,QWidget *>Tablist;
    QTextEdit *mainedit;
    QString mainfile;

public:

    QList<QMenu *> fGetMenuBar(){return menulist;}
    QMenu *fGetTextEditMenu(){return texteditmenu;}
    QList<QToolBar *> fGetToolBar(){return tblist;}
public slots:
    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();

    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textAlign(QAction *a);
    void setChecked(bool checked);
    void indent();
    void unindent();

    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();
    void about();
    void printPreview(QPrinter *);

    public:
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    bool maybeSave();

    void modifyIndentation(int amount);

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QAction *actionSave;
    QAction *actionTextBold;
    QAction *actionTextUnderline;
    QAction *actionTextItalic;
    QAction *actionTextColor;
    QAction *actionAlignLeft;
    QAction *actionAlignCenter;
    QAction *actionAlignRight;
    QAction *actionAlignJustify;
    QAction *actionIndentLess;
    QAction *actionIndentMore;
    QAction *actionToggleCheckState;
    QAction *actionUndo;
    QAction *actionRedo;
#ifndef QT_NO_CLIPBOARD
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
#endif

private:
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    QToolBar *tb;
    QList<QToolBar *>tblist;
    QList<QMenu *>menulist;
    QMenu *texteditmenu;
    QString fileName;
    QTextEdit *textEdit;
};

#endif // JTAB_H
