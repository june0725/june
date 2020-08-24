
#include "jtab.h"
#include "ui_jtab.h"
#include "june_main.h"

JTab::JTab(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::JTab)
{
    ui->setupUi(this);
   setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Ignored);
   textEdit = new QTextEdit(this);
   textEdit->setFrameShape(QFrame::NoFrame);
   connect(textEdit, &QTextEdit::currentCharFormatChanged,
           this, &JTab::currentCharFormatChanged);
   connect(textEdit, &QTextEdit::cursorPositionChanged,
           this, &JTab::cursorPositionChanged);

texteditmenu=new QMenu(tr("Text and Edit"),this);
   initActions();
   mainfile="Unamefile.txt";
addTab(textEdit,"Unamefile.txt");
}

JTab::~JTab()
{
    delete ui;
}

void JTab::changeindex(int i)
{
         QWidget * w=widget(i);
        QMap<QString, QWidget *>::const_iterator b = Tablist.constBegin();
        while (b != Tablist.constEnd())
        {
            if(b.value()==w)
            {
                if(QString(w->metaObject()->className())=="QTextEdit")
                {
                    if(Tablist.count()>1&&(QString(Tablist.value(mainfile)->metaObject()->className())=="QTextEdit"))
                    {
                        QString a=textEdit->toHtml();
                        dynamic_cast<QTextEdit *>(Tablist.value(mainfile))->setHtml(a);
                    }
                 }

                  mainfile=b.key();
                    tabfresh();
                    return;

                break;
            }
            ++b;
        }


}
void JTab::tabfresh()
{
    clear();
    QMap<QString, QWidget *>::const_iterator i = Tablist.constBegin();
    while (i != Tablist.constEnd())
    {
            if(i.key()==mainfile)
            {
                if(QString(i.value()->metaObject()->className())=="QTextEdit")
                {
                QString values=dynamic_cast<QTextEdit *>(i.value())->toHtml();
                textEdit->setHtml(values);
                addTab(textEdit,QFileInfo(i.key()).fileName());
                setCurrentWidget(textEdit);
                }
                else
                {
                    addTab(i.value(),QFileInfo(i.key()).fileName());
                    setCurrentWidget(i.value());
                }
            }
            else
            {
                 addTab(i.value(),QFileInfo(i.key()).fileName());
            }
        ++i;
    }


}
void JTab::addtabwidget(QWidget *w,QString f)
{
    Tablist.insert(f,w);
    mainfile=f;
    tabfresh();
}
bool JTab::addtabeditfile(QString f)
{
        if(!Tablist.contains(f))
        {
            QTextEdit *a=new QTextEdit(this);
            a->setFrameShape(QFrame::NoFrame);
            Tablist.insert(f,a);            
                fileopens(a,f);

        }


         if(Tablist.contains(mainfile)&&(QString(Tablist.value(mainfile)->metaObject()->className())=="QTextEdit"))
            {
                QString values=textEdit->toHtml();
                dynamic_cast<QTextEdit *>(Tablist.value(mainfile))->setHtml(values);
            }

            mainfile=f;
            tabfresh();
        return true;
}
void JTab::CloseChild(int i)
{
    if(Tablist.count()>1)
        changeindex(i);
    else
        changeindex(0);

    QWidget * w=widget(i);
   if(QString(w->metaObject()->className())=="QTextEdit")
   {
            maybeSave();
            removeTab(indexOf(textEdit));
            Tablist.remove(mainfile);
   }
   else
   {
       removeTab(indexOf(w));
       QMap<QString, QWidget *>::const_iterator a = Tablist.constBegin();
       while (a != Tablist.constEnd())
       {
           if(a.value()==w)
           {
               a.value()->deleteLater();
               Tablist.remove(a.key());
               break;
           }
           ++a;
       }


   }

}
void JTab::DbleClick(int i)
{
    changeindex(i);
    QWidget * w=widget(i);
   if(QString(w->metaObject()->className())=="QTextEdit")
   {
        if (mainfile.isEmpty()||mainfile=="Unamefile.txt")
            maybeSave();
        QString f=textEdit->toHtml();
        emit addmdi(f);
   }
}
void JTab::fileopens(QTextEdit *w, QString fn)
{
    if(!QFile::exists(fn))
    {
        w->setText("");
        return ;
    }

    QFile file(fn);
    if (!file.open(QFile::ReadOnly))
    {
        w->setText("");
        return ;
    }


    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        QUrl baseUrl = (fn.front() == QLatin1Char(':') ? QUrl(fn) : QUrl::fromLocalFile(fn)).adjusted(QUrl::RemoveFilename);
        w->document()->setBaseUrl(baseUrl);
        w->setHtml(str);
    } else {
#if QT_CONFIG(textmarkdownreader)
        QMimeDatabase db;
        if (db.mimeTypeForFileNameAndData(fn, data).name() == QLatin1String("text/markdown"))
            w->setMarkdown(QString::fromUtf8(data));
        else
#endif
            w->setPlainText(QString::fromUtf8(data));
    }


}
void JTab::initActions()
{

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    QAction *activenew = new QAction(newIcon,  tr("&New"), this);
    connect(activenew, &QAction::triggered, this, &JTab::fileNew);
    activenew->setStatusTip(tr("new an file"));
    activenew->setShortcut(QKeySequence::New);


    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png"));
    QAction *activeopen = new QAction(openIcon,  tr("&Open..."), this);
    connect(activeopen, &QAction::triggered, this, &JTab::fileOpen);
    activeopen->setStatusTip(tr("open an existing file"));
    activeopen->setShortcut(QKeySequence::Open);


    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png"));
    QAction *actionSave = new QAction(saveIcon,  tr("&Save"), this);
    connect(actionSave, &QAction::triggered, this, &JTab::fileSave);
    actionSave->setStatusTip(tr("save an file"));
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setEnabled(false);


    QAction *activesaveas = new QAction(tr("Save &As..."), this);
    connect(activesaveas, &QAction::triggered, this, &JTab::fileSaveAs);
    activesaveas->setStatusTip(tr("save as an new file"));


#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    const QIcon printIcon = QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png"));
    QAction *activeprint = new QAction(printIcon, tr("&Print..."), this);
    connect(activeprint, &QAction::triggered, this, &JTab::filePrint);
    activeprint->setShortcut(QKeySequence::Print);
    activeprint->setStatusTip(tr("print a file"));

    const QIcon filePrintIcon = QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png"));
    QAction *activeprintview=new QAction(filePrintIcon, tr("Print Preview..."), this);
    connect(activeprintview, &QAction::triggered, this, &JTab::filePrintPreview);
    activeprintview->setStatusTip(tr("file view first before print"));

    const QIcon exportPdfIcon = QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png"));
    QAction *activepdf = new QAction(exportPdfIcon, tr("&Export PDF..."), this);
    connect(activepdf, &QAction::triggered, this, &JTab::filePrintPdf);
    activepdf->setShortcut(Qt::CTRL + Qt::Key_D);
    activepdf->setStatusTip(tr("export a file to pdf format"));


#endif

    QAction *activequit = new QAction(tr("&Close"), this);
    connect(activequit, &QAction::triggered, this, &JTab::CloseAll);
    activequit->setShortcut(Qt::CTRL + Qt::Key_Q);
    activequit->setStatusTip(tr("export a file to pdf format"));

    const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png"));
    actionUndo = new QAction(undoIcon, tr("&Undo"), textEdit);
    connect(actionUndo, &QAction::triggered, textEdit, &QTextEdit::undo);
    actionUndo->setShortcut(QKeySequence::Undo);
    actionUndo->setStatusTip(tr("export a file to pdf format"));

    const QIcon redoIcon = QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png"));
    actionRedo = new QAction(redoIcon, tr("&Redo"), textEdit);
    connect(actionUndo, &QAction::triggered, textEdit, &QTextEdit::undo);
    actionRedo->setShortcut(QKeySequence::Redo);
    actionRedo->setStatusTip(tr("export a file to pdf format"));


#ifndef QT_NO_CLIPBOARD
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png"));
    actionCut = new QAction(cutIcon, tr("Cu&t"), textEdit);
    connect(actionUndo, &QAction::triggered, textEdit, &QTextEdit::cut);
    actionCut->setShortcut(QKeySequence::Cut);
    actionCut->setStatusTip(tr("export a file to pdf format"));


    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png"));
    actionCopy = new QAction(copyIcon, tr("&Copy"), textEdit);
    connect(actionUndo, &QAction::triggered, textEdit, &QTextEdit::copy);
    actionCopy->setShortcut(QKeySequence::Copy);
    actionCopy->setStatusTip(tr("export a file to pdf format"));


    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png"));
    actionPaste =new QAction(pasteIcon, tr("&Paste"), textEdit);
    connect(actionUndo, &QAction::triggered, textEdit, &QTextEdit::paste);
    actionPaste->setShortcut(QKeySequence::Paste);
    actionPaste->setStatusTip(tr("export a file to pdf format"));

    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif

    const QIcon boldIcon = QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png"));
    actionTextBold = new QAction(boldIcon, tr("&Bold"), this);
    connect(actionTextBold, &QAction::triggered, this, &JTab::textBold);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);

    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    actionTextBold->setCheckable(true);

    const QIcon italicIcon = QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png"));
    actionTextItalic = new QAction(italicIcon, tr("&Italic"), this);
    connect(actionTextItalic, &QAction::triggered, this, &JTab::textItalic);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    actionTextItalic->setCheckable(true);


    const QIcon underlineIcon = QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png"));
    actionTextUnderline = new QAction(underlineIcon, tr("&Underline"), this);
    connect(actionTextUnderline, &QAction::triggered, this, &JTab::textUnderline);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    actionTextUnderline->setCheckable(true);

    const QIcon leftIcon = QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png"));
    actionAlignLeft = new QAction(leftIcon, tr("&Left"), this);
    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setPriority(QAction::LowPriority);

    const QIcon centerIcon = QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png"));
    actionAlignCenter = new QAction(centerIcon, tr("C&enter"), this);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setPriority(QAction::LowPriority);

    const QIcon rightIcon = QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png"));
    actionAlignRight = new QAction(rightIcon, tr("&Right"), this);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignRight->setPriority(QAction::LowPriority);

    const QIcon fillIcon = QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png"));
    actionAlignJustify = new QAction(fillIcon, tr("&Justify"), this);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setPriority(QAction::LowPriority);

    const QIcon indentMoreIcon = QIcon::fromTheme("format-indent-more", QIcon(rsrcPath + "/format-indent-more.png"));
    actionIndentMore = new QAction(indentMoreIcon, tr("&Indent"), this);
    connect(actionIndentMore, &QAction::triggered, this, &JTab::indent);
    actionIndentMore->setShortcut(Qt::CTRL + Qt::Key_BracketRight);

    const QIcon indentLessIcon = QIcon::fromTheme("format-indent-less", QIcon(rsrcPath + "/format-indent-less.png"));
    actionIndentLess = new QAction(indentLessIcon, tr("&Unindent"), this);
    connect(actionIndentLess, &QAction::triggered, this, &JTab::unindent);
    actionIndentLess->setShortcut(Qt::CTRL + Qt::Key_BracketLeft);

    // Make sure the alignLeft  is always left of the alignRight
    alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &JTab::textAlign);

    if (QApplication::isLeftToRight()) {
        alignGroup->addAction(actionAlignLeft);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignRight);
    } else {
        alignGroup->addAction(actionAlignRight);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignLeft);
    }
    alignGroup->addAction(actionAlignJustify);


    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("&Color..."), this);
    connect(actionTextColor, &QAction::triggered, this, &JTab::textColor);

    const QIcon checkboxIcon = QIcon::fromTheme("status-checkbox-checked", QIcon(rsrcPath + "/checkbox-checked.png"));
    actionToggleCheckState = new QAction(checkboxIcon, tr("Chec&ked"), this);
    connect(actionToggleCheckState, &QAction::triggered, this, &JTab::setChecked);
    actionToggleCheckState->setShortcut(Qt::CTRL + Qt::Key_K);
    actionToggleCheckState->setCheckable(true);

    ////////////////////////////////////////////
    comboStyle = new QComboBox();
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Task List (Unchecked)");
    comboStyle->addItem("Task List (Checked)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    comboStyle->addItem("Heading 1");
    comboStyle->addItem("Heading 2");
    comboStyle->addItem("Heading 3");
    comboStyle->addItem("Heading 4");
    comboStyle->addItem("Heading 5");
    comboStyle->addItem("Heading 6");

    connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &JTab::textStyle);

    comboFont = new QFontComboBox();
    connect(comboFont, &QComboBox::textActivated, this, &JTab::textFamily);

    comboSize = new QComboBox();
    comboSize->setObjectName("comboSize");
    comboSize->setEditable(true);

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int size : standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
    connect(comboSize, &QComboBox::textActivated, this, &JTab::textSize);

///////////////////////////////////////////////////////////////////////////////////////////////////
   const QIcon insertIcon = QIcon::fromTheme("insertIcon", QIcon(":/images/june_icon.ico"));
    //插入表格
    QAction * act_insertTable = new QAction(insertIcon,QString("插入表格"),this);
    connect(act_insertTable,SIGNAL(triggered()),this,SLOT(insertTable()));
    act_insertTable->setStatusTip(tr("export a file to pdf format"));

    //插入列表
    QAction * act_insertList = new QAction(insertIcon,QString("插入列表"),this);
    connect(act_insertList,SIGNAL(triggered()),this,SLOT(insertList()));
    act_insertList->setStatusTip(tr("export a file to pdf format"));

    //插入图片
    QAction * act_insertImage = new QAction(insertIcon,QString("插入图片"),this);
    connect(act_insertImage,SIGNAL(triggered()),this,SLOT(insertImage()));
    act_insertImage->setStatusTip(tr("export a file to pdf format"));


    QAction * act_insertFrame = new QAction(insertIcon,QString("插入框架"),this);
    connect(act_insertFrame,SIGNAL(triggered()),this,SLOT(insertframe()));
    act_insertFrame->setStatusTip(tr("export a file to pdf format"));

    //查找
    QAction *act_find = new QAction(insertIcon,QString("查找"),this);
    connect(act_find,SIGNAL(triggered()),this,SLOT(textFind()));
    act_find->setStatusTip(tr("export a file to pdf format"));

    QAction *act_CHINA = new QAction(insertIcon,QString("中文"),this);
    connect(act_CHINA,SIGNAL(triggered()),this,SLOT(fOpenfile()));
    act_CHINA->setStatusTip(tr("export a file to pdf format"));

///////////////////////////////////////////////////////////////////////////////////////////////////
    QMenu *a=new QMenu(tr("Files"),this);
    a->addAction(activeopen);
    a->addAction(activenew);
    a->addAction(actionSave);
    a->addAction(activesaveas);
    a->addSeparator();
    a->addAction(activeprint);
    a->addAction(activeprintview);
    a->addAction(activepdf);
    a->addSeparator();
    a->addAction(activequit);

    QMenu *b=new QMenu(tr("Edits"),this);
    #ifndef QT_NO_CLIPBOARD
    b->addAction(actionCut);
    b->addAction(actionCopy);
    b->addAction(actionPaste);
    b->addSeparator();
    #endif
    b->addAction(actionUndo);
    b->addAction(actionRedo);
    b->addSeparator();


    QMenu *c=new QMenu(tr("Formats"),this);
    c->addAction(actionTextBold);
    c->addAction(actionTextUnderline);
    c->addAction(actionTextItalic);
    c->addAction(actionTextColor);
    c->addSeparator();
    c->addAction(actionToggleCheckState);
    c->addSeparator();
    c->addActions(alignGroup->actions());
    c->addSeparator();
   c->addAction(actionIndentLess);
   c->addAction(actionIndentMore);

   QMenu *d=new QMenu(tr("Inserts"),this);
   d->addAction(act_insertFrame);
   d->addAction(act_insertTable);
   d->addAction(act_insertList);
   d->addAction(act_insertImage);
   d->addAction(act_find);


texteditmenu->addMenu(a);
texteditmenu->addMenu(b);
texteditmenu->addMenu(c);
texteditmenu->addMenu(d);

QToolBar *ta=new QToolBar(tr("Edit Actions"));
ta->addAction(activenew);
ta->addAction(activeopen);

ta->addAction(actionSave);

ta->addSeparator();
ta->addAction(activeprint);

ta->addAction(activepdf);
ta->addSeparator();


#ifndef QT_NO_CLIPBOARD
ta->addAction(actionCut);
ta->addAction(actionCopy);
ta->addAction(actionPaste);
ta->addSeparator();
#endif
ta->addAction(actionUndo);
ta->addAction(actionRedo);
ta->addSeparator();
ta->addAction(actionTextBold);
ta->addAction(actionTextUnderline);
ta->addAction(actionTextItalic);
ta->addSeparator();
ta->addActions(alignGroup->actions());
ta->addSeparator();
ta->addAction(actionIndentLess);
ta->addAction(actionIndentMore);
ta->addSeparator();
ta->addAction(actionTextColor);
ta->addAction(actionToggleCheckState);
tblist.append(ta);

QToolBar *tb=new QToolBar(tr("Format Actions"));
tb->addWidget(comboStyle);
tb->addWidget(comboFont);
tb->addWidget(comboSize);
tb->addAction(act_find);
tb->addAction(act_insertTable);
tb->addAction(act_insertList);
tb->addAction(act_insertImage);
tb->addAction(act_insertFrame);
tb->addAction(act_CHINA);
tblist.append(tb);
//////////////////////////////////////////////////////////////////////
QFont textFont("Helvetica");
textFont.setStyleHint(QFont::SansSerif);
textEdit->setFont(textFont);
fontChanged(textEdit->font());
colorChanged(textEdit->textColor());
alignmentChanged(textEdit->alignment());

connect(textEdit->document(), &QTextDocument::modificationChanged,
        actionSave, &QAction::setEnabled);
connect(textEdit->document(), &QTextDocument::modificationChanged,
        this, &QWidget::setWindowModified);
connect(textEdit->document(), &QTextDocument::undoAvailable,
        actionUndo, &QAction::setEnabled);
connect(textEdit->document(), &QTextDocument::redoAvailable,
        actionRedo, &QAction::setEnabled);

setWindowModified(textEdit->document()->isModified());
actionSave->setEnabled(textEdit->document()->isModified());
actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

#ifndef QT_NO_CLIPBOARD
actionCut->setEnabled(false);
connect(textEdit, &QTextEdit::copyAvailable, actionCut, &QAction::setEnabled);
actionCopy->setEnabled(false);
connect(textEdit, &QTextEdit::copyAvailable, actionCopy, &QAction::setEnabled);

connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &JTab::clipboardDataChanged);
#endif
}
void JTab::insertTable()
{
    QTextCursor cursor =textEdit->textCursor();
    QTextTableFormat tableFormat;
    tableFormat.setCellPadding(10);
    tableFormat.setCellSpacing(2);
    cursor.insertTable(2,2,tableFormat);
}
void JTab::insertList()
{

        QTextCursor cursor = textEdit->textCursor();
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDecimal);
        cursor.insertList(listFormat);
}
void JTab::insertImage()
{
//    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
//                                  ".");
//    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
//    QImage image = QImageReader ( file ).read();

//    QTextDocument * textDocument = textEdit->document();
//    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = textEdit->textCursor();
    QTextImageFormat imageFormat;
//    imageFormat.setWidth( image.width() );
//    imageFormat.setHeight( image.height() );
    imageFormat.setName( ":/images/june_icon.png");
    cursor.insertImage(imageFormat);
}
void JTab::insertframe()
{
    QTextFrameFormat frameFormat2;
    frameFormat2.setBackground(Qt::lightGray);    //设置背景色
    frameFormat2.setMargin(10);        //设置边距
    frameFormat2.setPadding(5);        //设置填充
    frameFormat2.setBorder(2);
    frameFormat2.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);    //设置边框样式
    QTextCursor cursor = textEdit->textCursor();    //获取光标
    cursor.insertFrame(frameFormat2);
}
void JTab::textFind()
{
    En_Game *game=new En_Game();
    addtabwidget(game,"/home/pdw/june-Debug/word.db");

//    J_Word * w=new J_Word();
//    w->NewJWord("/home/pdw/june-Debug/t.db","data");
//    addtabwidget(w,"/home/pdw/june-Debug/t.db");

//    SQLiteData *maindataformat =new SQLiteData();
//    addtabwidget(maindataformat,"/home/pdw/june-Debug/main.db");

//    QDialog *dlg = new QDialog(this);       //创建查找对话框
//     lineEdit = new QLineEdit(dlg);          //创建字符串输入框
//     QPushButton* btFindNext = new QPushButton(this);    //查找按钮
//     btFindNext->setText(QString("查找下一个"));
//     connect(btFindNext,SIGNAL(clicked()),this,SLOT(findNext())); //关联查找信号和槽
//     QVBoxLayout* layout = new QVBoxLayout;      //垂直布局
//     layout->addWidget(lineEdit);                //将控件添加到主界面
//     layout->addWidget(btFindNext);
//     dlg->setLayout(layout);
//     dlg->show();
}
void JTab::findNext()
{


//        QString string = lineEdit->text();
//        //查找字符串，查找标志：QTextDocument::FindBackward:向前查找,
//        //FindWholeWords：整个文档查找,FindCaseSensitively：忽略大小写查找
//        bool isFind = textEdit->find(string,QTextDocument::FindWholeWords);
//        if (isFind) {
//            qDebug() << QString("行号:%1,列号:%2").arg(textEdit->textCursor().blockNumber())
//                        .arg(textEdit->textCursor().columnNumber());
//        }
}
bool JTab::maybeSave()
{
    if(Tablist.count()>0)
    {
    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("The document has been modified.\n"
                                "Do you want to save your changes?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    }
    else
    {
        if(!textEdit->toPlainText().isEmpty())
            fileSave();
    }


    return true;
}
void JTab::fileNew()
{
     maybeSave();     
    addtabeditfile("Unamefile.txt");
}
void JTab::fOpenfile()
{
    //////////////////中文编码显示
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);

    if(fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    if (!QFile::exists(fn))
        return ;
    QFile file(fn);
    if (!file.open(QFile::ReadOnly))
        return ;

      QByteArray data = file.readAll();

      QTextCodec *gbk = QTextCodec::codecForName("gb18030");
   //  QTextCodec *utf8 = QTextCodec::codecForName("utf-8");
//      QTextCodec *codec = Qt::codecForHtml(data);
      QString str = gbk->toUnicode(data);

    if (Qt::mightBeRichText(str)) {
        QUrl baseUrl = (fn.front() == QLatin1Char(':') ? QUrl(fn) : QUrl::fromLocalFile(fn)).adjusted(QUrl::RemoveFilename);
        textEdit->document()->setBaseUrl(baseUrl);
        textEdit->setHtml(str);
    } else {
#if QT_CONFIG(textmarkdownreader)
        QMimeDatabase db;
        if (db.mimeTypeForFileNameAndData(fn, data).name() == QLatin1String("text/markdown"))
            textEdit->setMarkdown(str);
        else
#endif
            textEdit->setText(str);
    }

    return;
}
void JTab::fileOpen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    if (fileDialog.exec() != QDialog::Accepted)
    {
        fileNew();
        return;
    }
    const QString fn = fileDialog.selectedFiles().first();
    if (QFile::exists(fn))
    {
            addtabeditfile(fn);
    }
    else
    {
        fileNew() ;
    }


}
void JTab::fileSave()
{    

    if(Tablist.count()==0)
    {
        fileSaveAs();
        if(!fileName.isEmpty())
        {
            QFile data(fileName);
            if (data.open(QFile::WriteOnly))
            {
                QTextStream out(&data);
                out <<textEdit->toHtml();
                out.flush();
            }
            mainfile=fileName;
            addtabeditfile(mainfile);
            tabfresh();
        }
        else
            textEdit->clear();

        return;
    }


    if (mainfile.isEmpty()||mainfile=="Unamefile.txt")
    {
        fileSaveAs();
        if(!fileName.isEmpty())
        {
            QFile data(fileName);
            if (data.open(QFile::WriteOnly))
            {
                QTextStream out(&data);
                out <<textEdit->toHtml();
                out.flush();
                removeTab(indexOf(textEdit));
                Tablist.remove(mainfile);
            }
            mainfile=fileName;
        }
        else
        {
            if(Tablist.count()>1)
                mainfile=Tablist.firstKey();
            else
                removeTab(indexOf(textEdit));

            return;
        }
    }
    else
    {
        if(QString(Tablist.value(mainfile)->metaObject()->className())!="QTextEdit")
            return;

        QFile data(mainfile);
        if (data.open(QFile::WriteOnly))
        {
            QTextStream out(&data);
            out <<textEdit->toHtml();
            out.flush();
            removeTab(indexOf(textEdit));
            Tablist.remove(mainfile);

        }
    }

    addtabeditfile(mainfile);
        tabfresh();

}
void JTab::fileSaveAs()
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
        fileName=fn;

    return;
}
void JTab::filePrint()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted)
        textEdit->print(&printer);
    delete dlg;
#endif
}
void JTab::filePrintPreview()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printpreviewdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &JTab::printPreview);
    preview.exec();
#endif
}
void JTab::printPreview(QPrinter *printer)
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    textEdit->print(printer);
#else
    Q_UNUSED(printer)
#endif
}
void JTab::filePrintPdf()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
//! [0]
    QFileDialog fileDialog(this, tr("Export PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    textEdit->document()->print(&printer);

#endif
}
void JTab::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}
void JTab::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
void JTab::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
void JTab::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}
void JTab::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}
void JTab::textStyle(int styleIndex)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;
    QTextBlockFormat::MarkerType marker = QTextBlockFormat::MarkerType::NoMarker;

    switch (styleIndex) {
    case 1:
        style = QTextListFormat::ListDisc;
        break;
    case 2:
        style = QTextListFormat::ListCircle;
        break;
    case 3:
        style = QTextListFormat::ListSquare;
        break;
    case 4:
        if (cursor.currentList())
            style = cursor.currentList()->format().style();
        else
            style = QTextListFormat::ListDisc;
        marker = QTextBlockFormat::MarkerType::Unchecked;
        break;
    case 5:
        if (cursor.currentList())
            style = cursor.currentList()->format().style();
        else
            style = QTextListFormat::ListDisc;
        marker = QTextBlockFormat::MarkerType::Checked;
        break;
    case 6:
        style = QTextListFormat::ListDecimal;
        break;
    case 7:
        style = QTextListFormat::ListLowerAlpha;
        break;
    case 8:
        style = QTextListFormat::ListUpperAlpha;
        break;
    case 9:
        style = QTextListFormat::ListLowerRoman;
        break;
    case 10:
        style = QTextListFormat::ListUpperRoman;
        break;
    default:
        break;
    }

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    if (style == QTextListFormat::ListStyleUndefined) {
        blockFmt.setObjectIndex(-1);
        int headingLevel = styleIndex >= 11 ? styleIndex - 11 + 1 : 0; // H1 to H6, or Standard
        blockFmt.setHeadingLevel(headingLevel);
        cursor.setBlockFormat(blockFmt);

        int sizeAdjustment = headingLevel ? 4 - headingLevel : 0; // H1 to H6: +3 to -2
        QTextCharFormat fmt;
        fmt.setFontWeight(headingLevel ? QFont::Bold : QFont::Normal);
        fmt.setProperty(QTextFormat::FontSizeAdjustment, sizeAdjustment);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.mergeCharFormat(fmt);
        textEdit->mergeCurrentCharFormat(fmt);
    } else {
        blockFmt.setMarker(marker);
        cursor.setBlockFormat(blockFmt);
        QTextListFormat listFmt;
        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }

    cursor.endEditBlock();
}
void JTab::textColor()
{
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}
void JTab::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}
void JTab::setChecked(bool checked)
{
    textStyle(checked ? 5 : 4);
}
void JTab::indent()
{
    modifyIndentation(1);
}
void JTab::unindent()
{
    modifyIndentation(-1);
}
void JTab::modifyIndentation(int amount)
{
    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();
    if (cursor.currentList()) {
        QTextListFormat listFmt = cursor.currentList()->format();
        // See whether the line above is the list we want to move this item into,
        // or whether we need a new list.
        QTextCursor above(cursor);
        above.movePosition(QTextCursor::Up);
        if (above.currentList() && listFmt.indent() + amount == above.currentList()->format().indent()) {
            above.currentList()->add(cursor.block());
        } else {
            listFmt.setIndent(listFmt.indent() + amount);
            cursor.createList(listFmt);
        }
    } else {
        QTextBlockFormat blockFmt = cursor.blockFormat();
        blockFmt.setIndent(blockFmt.indent() + amount);
        cursor.setBlockFormat(blockFmt);
    }
    cursor.endEditBlock();
}
void JTab::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}
void JTab::cursorPositionChanged()
{
    alignmentChanged(textEdit->alignment());
    QTextList *list = textEdit->textCursor().currentList();
    if (list) {
        switch (list->format().style()) {
        case QTextListFormat::ListDisc:
            comboStyle->setCurrentIndex(1);
            break;
        case QTextListFormat::ListCircle:
            comboStyle->setCurrentIndex(2);
            break;
        case QTextListFormat::ListSquare:
            comboStyle->setCurrentIndex(3);
            break;
        case QTextListFormat::ListDecimal:
            comboStyle->setCurrentIndex(6);
            break;
        case QTextListFormat::ListLowerAlpha:
            comboStyle->setCurrentIndex(7);
            break;
        case QTextListFormat::ListUpperAlpha:
            comboStyle->setCurrentIndex(8);
            break;
        case QTextListFormat::ListLowerRoman:
            comboStyle->setCurrentIndex(9);
            break;
        case QTextListFormat::ListUpperRoman:
            comboStyle->setCurrentIndex(10);
            break;
        default:
            comboStyle->setCurrentIndex(-1);
            break;
        }
        switch (textEdit->textCursor().block().blockFormat().marker()) {
        case QTextBlockFormat::MarkerType::NoMarker:
            actionToggleCheckState->setChecked(false);
            break;
        case QTextBlockFormat::MarkerType::Unchecked:
            comboStyle->setCurrentIndex(4);
            actionToggleCheckState->setChecked(false);
            break;
        case QTextBlockFormat::MarkerType::Checked:
            comboStyle->setCurrentIndex(5);
            actionToggleCheckState->setChecked(true);
            break;
        }
    } else {
        int headingLevel = textEdit->textCursor().blockFormat().headingLevel();
        comboStyle->setCurrentIndex(headingLevel ? headingLevel + 10 : 0);
    }
}
void JTab::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}
void JTab::CloseAll()
{
    if(Tablist.count()==0)
    {
        maybeSave();
        return;
    }


    while (Tablist.count()>0)
        {
            CloseChild(0);
        }

}
void JTab::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}
void JTab::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}
void JTab::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}
void JTab::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft)
        actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        actionAlignJustify->setChecked(true);
}


