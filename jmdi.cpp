
#include "jmdi.h"
#include "ui_jmdi.h"

JMdi::JMdi(QWidget *parent) :
    QMdiArea(parent),
    ui(new Ui::JMdi)
{
    ui->setupUi(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

JMdi::~JMdi()
{
   delete ui;
}

bool JMdi::AddMainEdit(JTab *tabedit)
{
    addSubWindow(tabedit,Qt::WindowMinMaxButtonsHint);
    return true;
}
bool JMdi::AddmdiChild(QWidget *w)
{
    QMdiSubWindow *subwin1 = addSubWindow(w);
    subwin1->setAttribute(Qt::WA_DeleteOnClose);
    subwin1->show();

    return true;
}

bool JMdi::AddeditChild(const QString f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;
    textEdit=new QTextEdit(this);
    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        QUrl baseUrl = (f.front() == QLatin1Char(':') ? QUrl(f) : QUrl::fromLocalFile(f)).adjusted(QUrl::RemoveFilename);
        textEdit->document()->setBaseUrl(baseUrl);
        textEdit->setHtml(str);
    } else {
#if QT_CONFIG(textmarkdownreader)
        QMimeDatabase db;
        if (db.mimeTypeForFileNameAndData(f, data).name() == QLatin1String("text/markdown"))
            textEdit->setMarkdown(QString::fromUtf8(data));
        else
#endif
            textEdit->setPlainText(QString::fromUtf8(data));
    }
    textEdit->setReadOnly(true);
    QMdiSubWindow *subwin1 = addSubWindow(textEdit);
    subwin1->setAttribute(Qt::WA_DeleteOnClose);
    subwin1->setWindowTitle(QFileInfo(f).fileName());
    subwin1->show();

    return true;
}


