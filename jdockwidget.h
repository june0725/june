#ifndef JDOCKWIDGET_H
#define JDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class JDockWidget;
}

class JDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit JDockWidget(QWidget *parent = nullptr);
    ~JDockWidget();

private:
    Ui::JDockWidget *ui;
};

#endif // JDOCKWIDGET_H
