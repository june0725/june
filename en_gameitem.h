#ifndef EN_GAMEITEM_H
#define EN_GAMEITEM_H

#include <QColor>
#include <QPainterPath>
#include <QPoint>
#include <QRandomGenerator>
class En_Gameitem
{
public:
    En_Gameitem();
    void setPath(const QPainterPath &path);
    void setToolTip(const QString &toolTip);
    void setPosition(const QPoint &position);
    void setColor(const QColor &color);
    void setIndex(const int &i);

    QPainterPath path() const;
    QPoint position() const;
    QColor color() const;
    QString toolTip() const;
    int indexs() const;

private:
    QPainterPath myPath;
    QPoint myPosition;
    QColor myColor;
    QString myToolTip;
    int index;
};

#endif // EN_GAMEITEM_H
