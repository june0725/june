#ifndef JTEXTEDIT_H
#define JTEXTEDIT_H


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
#include <QTextEdit>
#include <QPainter>
#include <QTextBlock>


QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

class JTextEdit : public QTextEdit
{
    Q_OBJECT
public:
   explicit JTextEdit(QWidget *parent = nullptr);
    ~JTextEdit();
    /////////////////////////////////



    /////////////////////
public:
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth(int c);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int BlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
public:
    /////////////////////////////////////
    QString getfilename(){return filename;}
    void setfilename(QString f){filename=f;}
    //////////////////////////////////
    void fileopen(QString f);
    void filesave();
    void textformat();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();
    void printPreview(QPrinter *);
    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textColor(const QString &c);
    void textAlignleft(){setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);}
    void textAlignright(){setAlignment(Qt::AlignRight | Qt::AlignAbsolute);}
    void textAligncenter(){setAlignment(Qt::AlignHCenter);};
    void textAlignjustify(){setAlignment(Qt::AlignJustify);}
    void indent(){modifyIndentation(1);}
    void unindent(){modifyIndentation(-1);}
    void insertTable();     //插入表格
    void insertList();      //插入列表
    void insertImage();
    void insertframe();
    void textFind();        //文本查找
    void findNext();
    void modifyIndentation(int amount);
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

    QString filename;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(JTextEdit *editor) : QWidget(editor), codeEditor(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(codeEditor->document()->blockCount()), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    JTextEdit *codeEditor;
};

#endif // JTEXTEDIT_H
