
#include "june_main.h"
#include "ui_june_main.h"


June_Main::June_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::June_Main)
{
    ui->setupUi(this);

    mdiArea=new JMdiArea(this);
    setCentralWidget(mdiArea);
    mdiArea->showMaximized();


//    setWindowIcon(QIcon(":/images/june.png"));
//    mdiArea=new JMdi(this);
//    setCentralWidget(mdiArea);
//    mdiArea->showMaximized();
//    tabedit=new JTab(this);
// connect(tabedit,&JTab::addmdi,mdiArea,&JMdi::AddeditChild);

// menuBar()->addMenu(tabedit->fGetTextEditMenu());

//      QToolBar *t;
//      foreach(t,tabedit->fGetToolbarlist())
//      {
//          addToolBar(t);
//          addToolBarBreak(Qt::TopToolBarArea);
//      }
//       mdiArea->AddMainEdit(tabedit);
/////////////////////////////////////////////////////////////////////////
       comboFont = new QFontComboBox(ui->toolBar_2);
       comboFont->setObjectName("comboFont");
       ui->toolBar_2->addWidget(comboFont);
       connect(comboFont, &QComboBox::textActivated, this, &June_Main::sactionfont);

       comboSize = new QComboBox(ui->toolBar_2);
       comboSize->setObjectName("comboSize");
       ui->toolBar_2->addWidget(comboSize);
        connect(comboSize, &QComboBox::textActivated, this, &June_Main::sactionsize);
       const QList<int> standardSizes = QFontDatabase::standardSizes();
       for (int size : standardSizes)
           comboSize->addItem(QString::number(size));
       comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

     comboColor = new QComboBox(ui->toolBar_2);
     comboColor->setObjectName("comboColor");
       ui->toolBar_2->addWidget(comboColor);
        connect(comboColor, &QComboBox::textActivated, this, &June_Main::sactioncolor);
       QStringList colors=QColor::colorNames();
       for (QString color:colors)
       comboColor->addItem(color);
//////////////////////////////////////////////////////////////
}

June_Main::~June_Main()
{

    delete ui;
}

void June_Main::sactionfont(QString f)
{
    if(mdiArea->Getactiveedit())
    mdiArea->Getactiveedit()->textFamily(f);
}
void June_Main::sactionsize(QString s)
{
    if(mdiArea->Getactiveedit())
    mdiArea->Getactiveedit()->textSize(s);
}
void June_Main::sactioncolor(QString c)
{
    if(mdiArea->Getactiveedit())
    mdiArea->Getactiveedit()->textColor(c);
}
///////////////////
void June_Main::sactionadd(){}
void June_Main::sactionblack()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->textBold();
}
void June_Main::sactioncatalog(){}
void June_Main::sactioncenter()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->textAligncenter();
}
void June_Main::sactioncodestyle()
{

}
void June_Main::sactionexam(){}
void June_Main::sactionexplain(){}
void June_Main::sactionform(){}
void June_Main::sactionfound(){}
void June_Main::sactionfream(){}
void June_Main::sactionguess(){}
void June_Main::sactionhelp(){}
void June_Main::sactionhtml()
{
    JTextEdit *edit =mdiArea->Getactiveedit();

   // qDebug()<<file.fileName()<<file.exists();

        QFileDialog fileDialog(this, tr("Save as..."));
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        if (fileDialog.exec() != QDialog::Accepted)
            return;
        const QString fn = fileDialog.selectedFiles().first();

    QFile file(fn);
    if (file.open(QFile::WriteOnly))
    {
        QTextStream out(&file);
        out <<edit->toHtml();
        out.flush();
    }
    file.close();
    mdiArea->Addchildren(fn)->setHtml(edit->toHtml());
}
void June_Main::sactionitalic()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->textItalic();
}
void June_Main::sactionjust()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->textAlignjustify();
    qDebug()<<"just";
}
void June_Main::sactionleft()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->textAlignleft();
}
void June_Main::sactionlist(){}
void June_Main::sactionlisten(){}
void June_Main::sactionnew()
{
     mdiArea->Addchildren("new");
}
void June_Main::sactionopen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    if (fileDialog.exec() != QDialog::Accepted)
        return;

    const QString f = fileDialog.selectedFiles().first();
    JTextEdit *edit=mdiArea->Addchildren(f);
     QFile file(f);
     if (!file.open(QFile::ReadOnly)||!edit)
         return ;
     QByteArray data = file.readAll();
    //QTextCodec *codec = Qt::codecForHtml(data);
    // QTextCodec *codec = QTextCodec::codecForName("gb18030");
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
     QString str = codec->toUnicode(data);
     if (Qt::mightBeRichText(str)) {
         QUrl baseUrl = (f.front() == QLatin1Char(':') ? QUrl(f) : QUrl::fromLocalFile(f)).adjusted(QUrl::RemoveFilename);
        edit->document()->setBaseUrl(baseUrl);
         edit->setHtml(str);
     } else {
 #if QT_CONFIG(textmarkdownreader)
         QMimeDatabase db;
         if (db.mimeTypeForFileNameAndData(f, data).name() == QLatin1String("text/markdown"))
             edit->setMarkdown(str);
         else
 #endif
            edit->setPlainText(str);
     }

     file.close();
}
void June_Main::sactionpdf()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->filePrintPdf();
}
void June_Main::sactionpicture(){}
void June_Main::sactionplain()
{
    if(mdiArea)
        mdiArea->setViewMode(QMdiArea::SubWindowView);
}
void June_Main::sactionpreview()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->filePrintPreview();
}
void June_Main::sactionprint()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->filePrint();
}
void June_Main::sactionprogress(){}
void June_Main::sactionread(){}
void June_Main::sactionright()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->textAlignright();
}
void June_Main::sactionsave()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    QFile file(edit->getfilename());

    if(!file.exists())
    {
        QFileDialog fileDialog(this, tr("Save as..."));
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        if (fileDialog.exec() != QDialog::Accepted)
            return;
        const QString fn = fileDialog.selectedFiles().first();
            edit->setfilename(fn);
            file.setFileName(fn);
            mdiArea->currentSubWindow()->setWindowTitle(fn);
    }

    if (file.open(QFile::WriteOnly))
    {
        QTextStream out(&file);
        out <<edit->toHtml();
        out.flush();
    }
    file.close();

}
void June_Main::sactionset(){}
void June_Main::sactionsetting(){}
void June_Main::sactionsort(){}
void June_Main::sactionsource(){}
void June_Main::sactionspeak(){}
void June_Main::sactionstyle(){}
void June_Main::sactiontab()
{
    if(mdiArea)
        mdiArea->setViewMode(QMdiArea::TabbedView);
}
void June_Main::sactiontable(){}
void June_Main::sactiontest(){}
void June_Main::sactiontext()
{
    JTextEdit *edit =mdiArea->Getactiveedit();

   // qDebug()<<file.fileName()<<file.exists();

        QFileDialog fileDialog(this, tr("Save as..."));
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        if (fileDialog.exec() != QDialog::Accepted)
            return;
        const QString fn = fileDialog.selectedFiles().first();

    QFile file(fn);
    if (file.open(QFile::WriteOnly))
    {
        QTextStream out(&file);
        out <<edit->toPlainText();
        out.flush();
    }
    file.close();
    mdiArea->Addchildren(fn)->setPlainText(edit->toPlainText());
}
void June_Main::sactionticket(){}
void June_Main::sactiontips(){}
void June_Main::sactionunder()
{
    JTextEdit *edit =mdiArea->Getactiveedit();
    if(edit)
        edit->textUnderline();
}
void June_Main::sactionwrite(){}


