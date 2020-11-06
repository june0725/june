#ifndef J_EDIT_H
#define J_EDIT_H

#include <QWidget>
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
#include <QImageReader>
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

const QString rsrcPath = ":/images/icon";

namespace Ui {
class J_Edit;
}

class J_Edit : public QWidget
{
    Q_OBJECT

public:
    explicit J_Edit(QWidget *parent = nullptr);
    ~J_Edit();
    QMenu *fGetTextEditMenu(){return texteditmenu;}
    QList<QToolBar *> fGetToolbarlist(){return tblist;}
    void initActions();

public slots:


private:
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QList<QToolBar *>tblist;
    QMenu *texteditmenu;
    QTextEdit *textEdit;
    QString fileName;

public slots:
    void fileNew();
    void fileOpen();
    void fOpenfile();
    void fileSave();
    void fileSaveAs();
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
    void CloseAll();
    void printPreview(QPrinter *);

    ///////////////////////////
    void insertTable();     //插入表格
     void insertList();      //插入列表
       void insertImage();
       void insertframe();
       void textFind();        //文本查找
       void findNext();
    public:
    bool maybeSave();
    void modifyIndentation(int amount);
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    ///////////////////////////////////////////
    QAction *activenew;
    QAction *activeopen;
    QAction *actionSave;
    QAction *activesaveas;
    QAction *activeprint;
    QAction *activeprintview;
    QAction *activepdf;
    QAction *activequit;
////////////////////////////////////////
    QActionGroup *alignGroup;
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
/////////////////////////////////////
    QAction *actionUndo;
    QAction *actionRedo;
#ifndef QT_NO_CLIPBOARD
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
#endif
    ///////////////////////
    QAction *act_insertFrame;
    QAction *act_insertTable;
    QAction *act_insertList;
    QAction *act_insertImage;
    QAction *act_find;
    QAction *act_CHINA;
private:
    Ui::J_Edit *ui;
};

#endif // J_EDIT_H
