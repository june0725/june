#include "en_gameitem.h"

En_Gameitem::En_Gameitem()
{
    myPath.addRect(QRect(0, 0, 50, 50));
    myColor=QColor(0, 0, 255,1);
    myPosition=QPoint(QRandomGenerator::global()->bounded(800), QRandomGenerator::global()->bounded(600));
    myToolTip=QString("?");
    index=0;
}
int En_Gameitem::indexs() const
{
    return index;
}
QPainterPath En_Gameitem::path() const
{
    return myPath;
}
//! [0]

//! [1]
QPoint En_Gameitem::position() const
{
    return myPosition;
}
//! [1]

//! [2]
QColor En_Gameitem::color() const
{
    return myColor;
}
//! [2]

//! [3]
QString En_Gameitem::toolTip() const
{
    return myToolTip;
}
//! [3]
void En_Gameitem::setIndex(const int &i)
{
    index=i;
}
//! [4]
void En_Gameitem::setPath(const QPainterPath &path)
{
    myPath = path;
}
//! [4]

//! [5]
void En_Gameitem::setToolTip(const QString &toolTip)
{
    myToolTip = toolTip;
}
//! [5]

//! [6]
void En_Gameitem::setPosition(const QPoint &position)
{
    myPosition = position;
}
//! [6]

//! [7]
void En_Gameitem::setColor(const QColor &color)
{
    myColor = color;
}
//! [7]
