#include "jdockwidget.h"
#include "ui_jdockwidget.h"

JDockWidget::JDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::JDockWidget)
{
    ui->setupUi(this);
    setAllowedAreas(Qt::AllDockWidgetAreas);
}

JDockWidget::~JDockWidget()
{
    delete ui;
}
