#ifndef EN_GAME_H
#define EN_GAME_H

#include <QWidget>
#include <QMouseEvent>
#include <QIcon>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyle>
#include <QToolButton>
#include <QToolTip>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFileInfo>
#include <QDialog>
#include <QProcess>

#include "en_gameitem.h"
#include "qsqlite3_database.h"

namespace Ui {
class En_Game;
}

class En_Game : public QDialog
{
    Q_OBJECT

public:
    explicit En_Game(QWidget *parent = nullptr);
    ~En_Game();
    void updatagame(QString en,QString ch);

protected:   
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event)override;
    void isRight();


private slots:
    void wordfileopen();
    void learnmodel(){model="learn";};
    void exammodel(){model="exam";};
    void usekeybordset(){(usekey)?usekey=false:true;};
    void gamestart();

//! [0]

//! [1]
private:
    void createShapeItem();
    void updataLetterSheet();
    int itemAt(const QPoint &pos);
    int itemin(const QPoint &pos);
    void createGameBaseLetter();
    void initLetterSheet();
    void initLetter();
    void initdatabase();
    void createActions();

    QString En;
    QString Ch;
    int EnMaxCount=13;
    int EachSize=53;
    int EachRow=10;
    int EachCross=4;
    QPoint LetterSheet=QPoint(110,380);
    QPoint LetterStart=QPoint(50,80);
    QPoint Chpoint=QPoint(70,150);
    QRect Chrectangle=QRect(0,0,580,220);
    QString GameBaseLetter;
    ////////////////////////////
    QVector<En_Gameitem> shapeItems;
    QVector<En_Gameitem> LettersKeybords;
    ///////////
    QPoint scorPoint=QPoint(550,20);
    QRect scorrectangle=QRect(0,0,250,40);
    int rightscor=10000;
    int allscor=200000;
    ////////////

    QList<QSqlRecord >word;
    ////////

    ///
    bool usekey;
    QString model;
    QString filename;
    //创建菜单、菜单项
    QMenu *pop_menu;
    QAction *wordfile;
    QAction *learn;
    QAction *exam;
    QAction *usekeybord;
    QAction *startgame;

private:
    Ui::En_Game *ui;
};

#endif // EN_GAME_H
