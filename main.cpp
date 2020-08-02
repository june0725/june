#include "june_main.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    June_Main w;
    w.show();
    return a.exec();
}
