#include "jmdiarea.h"

JMdiArea::JMdiArea(QWidget *parent):QMdiArea(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
setViewMode(QMdiArea::TabbedView);
setTabsClosable(true);
setTabsMovable(true);
setTabShape(QTabWidget::Triangular);
}

JMdiArea::~JMdiArea()
{

}

JTextEdit * JMdiArea::Addchildren(QString n)
{
    QMdiSubWindow *subWindow=activeSubWindow();
    if(subWindow)
    {
        QList<QMdiSubWindow *> sublist=subWindowList();
        subWindow=nullptr;
        foreach(subWindow,sublist)
        {
          if(n==dynamic_cast<JTextEdit *>(subWindow->widget())->getfilename())
             {
              subWindow->setFocus();
                return dynamic_cast<JTextEdit *>(subWindow->widget());
              }
        }
    }


    JTextEdit * edit=new JTextEdit(this);
   edit->setfilename(n);
    subWindow =addSubWindow(edit);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowTitle(n);
     subWindow->showMaximized();
    return edit;
}

JTextEdit *JMdiArea::Getactiveedit()
{
    QMdiSubWindow *sub=activeSubWindow();
    if(sub)
    return dynamic_cast<JTextEdit *>(sub->widget());

    return nullptr;
}
