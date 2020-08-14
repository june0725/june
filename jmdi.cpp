
#include "jmdi.h"
#include "ui_jmdi.h"

JMdi::JMdi(QWidget *parent) :
    QMdiArea(parent),
    ui(new Ui::JMdi)
{
    ui->setupUi(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setBackground(QBrush(QImage(":/images/june_icon.png")));
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
    QMdiSubWindow *subWindow1 =addSubWindow(w);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);    
    subWindow1->show();
    tileSubWindows();
    return true;
}

bool JMdi::AddeditChild(const QString f)
{
    textEdit=new QTextEdit(this);
    textEdit->setText(f);
    textEdit->setReadOnly(true);
    QMdiSubWindow *subWindow1 =addSubWindow(textEdit);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->show();
    tileSubWindows();
    return true;
}


