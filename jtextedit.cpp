#include "jtextedit.h"

JTextEdit::JTextEdit(QWidget *parent) :QTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    connect(this, &JTextEdit::cursorPositionChanged, this, &JTextEdit::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

JTextEdit::~JTextEdit()
{

}

int JTextEdit::lineNumberAreaWidth(int c)
{
    int digits = 1;
    int max = qMax(1, c);
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void JTextEdit::updateLineNumberAreaWidth(int BlockCount)
{
    setViewportMargins(lineNumberAreaWidth(BlockCount), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void JTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

//![slotUpdateRequest]

//![resizeEvent]

void JTextEdit::resizeEvent(QResizeEvent *event)
{
    QTextEdit::resizeEvent(event);
      QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(this->document()->blockCount()), cr.height()));
}

//![resizeEvent]

void JTextEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
       {
          // qDebug()<<"EnterKey";
       }
    QTextEdit::keyPressEvent(event);
    updateLineNumberAreaWidth(this->document()->blockCount());
}
void JTextEdit::keyReleaseEvent(QKeyEvent *event)
{
    QTextEdit::keyReleaseEvent(event);
}
void JTextEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTextEdit::mouseDoubleClickEvent(event);
}
void JTextEdit::mousePressEvent(QMouseEvent *event)
{
    //获取点击的下标
    qDebug() << event->x() << ":" << event->y();
    if(event->button() == Qt::LeftButton)
    {
       // qDebug() << "左键" ;
    }
    else if(event->button() == Qt::RightButton)
    {
       // qDebug() << "右键" ;
    }

    // 获取鼠标在点击窗体上的坐标
       QPoint pos = event->pos();
       qDebug()<<pos;
       if(event->modifiers()==Qt::ShiftModifier)
       {
           if(event->button() == Qt::LeftButton)
           {
               //qDebug()<<"ShiftKey + MOuseLeftButton";
               return;
           }
       }
       if(event->modifiers()==Qt::ControlModifier)
       {
           if(event->button() == Qt::RightButton)
           {
            //   qDebug()<<"ControlKey + MOuseRightButton";
               return;
           }
       }
    QTextEdit::mousePressEvent(event);
}
void JTextEdit::mouseReleaseEvent(QMouseEvent *event)
{
    QTextEdit::mouseReleaseEvent(event);
}
void JTextEdit::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()>0)
    {
       // qDebug() << "上滚";
    }
    else
    {
       // qDebug() << "下滚";
    }


}
//![cursorPositionChanged]

void JTextEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void JTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block =document()->firstBlock();
    int top = qRound(0.0);
    int bottom =qRound(0.0);
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid()) {
        if (block.isVisible()) {
            qDebug()<<block.blockNumber();
            qDebug()<<top;
            bottom=block.layout()->boundingRect().height();
            QString number = QString::number(block.blockNumber() + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
            top=top+bottom;
            }
        block = block.next();        
    }
}
//![extraAreaPaintEvent_2]
void JTextEdit::fileopen(QString f)
{

}

void JTextEdit::filesave()
{


}
void JTextEdit::insertTable()
{
    QTextCursor cursor =textCursor();
    QTextTableFormat tableFormat;
    tableFormat.setCellPadding(10);
    tableFormat.setCellSpacing(2);
    cursor.insertTable(2,2,tableFormat);
}
void JTextEdit::insertList()
{

        QTextCursor cursor =textCursor();
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDecimal);
        cursor.insertList(listFormat);
}
void JTextEdit::insertImage()
{
//    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
//                                  ".");
//    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
//    QImage image = QImageReader ( file ).read();

//    QTextDocument * textDocument = textEdit->document();
//    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = textCursor();
    QTextImageFormat imageFormat;
//    imageFormat.setWidth( image.width() );
//    imageFormat.setHeight( image.height() );
    imageFormat.setName( ":/images/june_icon.png");
    cursor.insertImage(imageFormat);
}
void JTextEdit::insertframe()
{
//    QTextFrameFormat frameFormat2;
//    frameFormat2.setBackground(Qt::lightGray);    //设置背景色
//    frameFormat2.setMargin(10);        //设置边距
//    frameFormat2.setPadding(5);        //设置填充
//    frameFormat2.setBorder(2);
//    frameFormat2.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);    //设置边框样式
//    QTextCursor cursor = textEdit->textCursor();    //获取光标
//    cursor.insertFrame(frameFormat2);

    //qDebug()<<toPlainText();
}
void JTextEdit::textFind()
{


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
void JTextEdit::findNext()
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
void JTextEdit::filePrint()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted)
        print(&printer);
    delete dlg;
#endif
}
void JTextEdit::filePrintPreview()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printpreviewdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &JTextEdit::printPreview);
    preview.exec();
#endif
}
void JTextEdit::printPreview(QPrinter *printer)
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    print(printer);
#else
    Q_UNUSED(printer)
#endif
}
void JTextEdit::filePrintPdf()
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
    document()->print(&printer);

#endif
}
void JTextEdit::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(QFont::Bold);
    mergeFormatOnWordOrSelection(fmt);
}
void JTextEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(true);
    mergeFormatOnWordOrSelection(fmt);
}
void JTextEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(true);
    mergeFormatOnWordOrSelection(fmt);
}
void JTextEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}
void JTextEdit::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void JTextEdit::textColor(const QString &c)
{
    QColor col(c);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
}
void JTextEdit::modifyIndentation(int amount)
{
    QTextCursor cursor = textCursor();
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

void JTextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    mergeCurrentCharFormat(format);
}
