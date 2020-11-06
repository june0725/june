#ifndef JDOCKWIDGETS_H
#define JDOCKWIDGETS_H

#include <QDockWidget>

class JDockWidgets : public QDockWidget
{
    Q_OBJECT
public:
    explicit JDockWidgets(QWidget *parent = nullptr);
    //~JDockWidgets();
};

#endif // JDOCKWIDGETS_H
