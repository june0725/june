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
#include "june_main.h"
#include "ui_june_main.h"




June_Main::June_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::June_Main)
{
    ui->setupUi(this);
    mdiArea=new JMdi(this);
    setCentralWidget(mdiArea);
    mdiArea->showMaximized();

       tabedit=new JTab(this);


 menuBar()->addMenu(tabedit->fGetTextEditMenu());

      QToolBar *t;
      foreach(t,tabedit->fGetToolBar())
      {
          addToolBar(t);
      }
       mdiArea->AddMainEdit(tabedit);
}

June_Main::~June_Main()
{

    delete ui;
}

//void June_Main::createMdi()
//{

//   connect(mdiArea, &QMdiArea::subWindowActivated,this, &MainWindow::updateMenus);

//    setWindowTitle(QCoreApplication::applicationName());

//    textEdit = new QTextEdit(this);
//    textEdit->setFrameShape(QFrame::NoFrame);

//    connect(textEdit, &QTextEdit::currentCharFormatChanged,
//            this, &June_Main::currentCharFormatChanged);
//    connect(textEdit, &QTextEdit::cursorPositionChanged,
//            this, &June_Main::cursorPositionChanged);


//    setToolButtonStyle(Qt::ToolButtonFollowStyle);
//    setupFileActions();
//    setupEditActions();
//    setupTextActions();

//    {
//        QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
//        helpMenu->addAction(tr("About"), this, &June_Main::about);
//        helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
//    }

//    QFont textFont("Helvetica");
//    textFont.setStyleHint(QFont::SansSerif);
//    textEdit->setFont(textFont);
//    fontChanged(textEdit->font());
//    colorChanged(textEdit->textColor());
//    alignmentChanged(textEdit->alignment());

//    connect(textEdit->document(), &QTextDocument::modificationChanged,
//            actionSave, &QAction::setEnabled);
//    connect(textEdit->document(), &QTextDocument::modificationChanged,
//            this, &QWidget::setWindowModified);
//    connect(textEdit->document(), &QTextDocument::undoAvailable,
//            actionUndo, &QAction::setEnabled);
//    connect(textEdit->document(), &QTextDocument::redoAvailable,
//            actionRedo, &QAction::setEnabled);

//    setWindowModified(textEdit->document()->isModified());
//    actionSave->setEnabled(textEdit->document()->isModified());
//    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
//    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

//#ifndef QT_NO_CLIPBOARD
//    actionCut->setEnabled(false);
//    connect(textEdit, &QTextEdit::copyAvailable, actionCut, &QAction::setEnabled);
//    actionCopy->setEnabled(false);
//    connect(textEdit, &QTextEdit::copyAvailable, actionCopy, &QAction::setEnabled);

//    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &June_Main::clipboardDataChanged);
//#endif


//}
//void June_Main::createTabWidget()
//{
//    if(!mdiArea)
//        createMdi();
 //   tabedit=new JTab(this);
//    setMenuBar(tabedit->fGetMenuBar());
//    mdiArea->AddMainEdit(tabedit);
//    tabedit->addmainedit(textEdit);
//   tabedit->showMaximized();
//    connect(tabedit,&JTab::addmdi,mdiArea,&JMdi::AddeditChild);
//    J_Word *jw=new J_Word(this);
//    jw->NewJWord("./sound/word.db","word");
//    tabedit->addtabwidget(jw,"./sound/word.db");

//}
//void June_Main::createDock()
//{
//    JDockWidget * dw=new JDockWidget(this);
//    J_Word *jw=new J_Word(this);
//    jw->NewJWord("./sound/word.db","word");
//    addDockWidget(Qt::RightDockWidgetArea, dw);
//    dw->setWidget(jw);
//    dock << dw;
//}

