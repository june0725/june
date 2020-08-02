#include "en_game.h"
#include "ui_en_game.h"

En_Game::En_Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::En_Game)
{
    ui->setupUi(this);
    setMinimumSize(800,600);
    setBackgroundRole(QPalette::Base);
    En="";
    Ch="";
    rightscor=0;
    allscor=0;
    usekey=false;
    model="exam";
    filename="word.db";



    initLetterSheet();
    initLetter();
    initdatabase();
    createActions();
}

En_Game::~En_Game()
{
    delete ui;

}

void En_Game::createActions()
{    //创建菜单、菜单项
    pop_menu = new QMenu();
    startgame=new QAction(tr("开始新游戏"),this);
    wordfile = new QAction(tr("加载数据文件"),this);
    learn = new QAction(tr("开始学习模式"),this);
    exam = new QAction(tr("开始测试模式"),this);
    usekeybord = new QAction(tr("键盘设置"),this);
    //连接信号与槽
    connect(wordfile, &QAction::triggered, this, &En_Game::wordfileopen);
    connect(learn, &QAction::triggered, this, &En_Game::learnmodel);
    connect(exam, &QAction::triggered, this, &En_Game::exammodel);
    connect(usekeybord, &QAction::triggered, this, &En_Game::usekeybordset);
    connect(startgame, &QAction::triggered, this, &En_Game::gamestart);

}
void En_Game::wordfileopen()
{
    QString path=QFileDialog::getOpenFileName(this,tr("Open database file"),".",tr("database file(*.db)"));
    QFileInfo filenames(path);
    filename=filenames.fileName();
    En="";
    Ch="";
    rightscor=0;
    allscor=0;
    initdatabase();
    gamestart();

}
void En_Game::gamestart()
{
     QString explains;
    explains=word.at(allscor).value("Explain").toString();
    explains.replace("&","\n");
    explains=word.at(allscor).value("PhoneticE").toString()+"\n"+word.at(allscor).value("PhoneticA").toString()+"\n\n"+explains;
    updatagame(word.at(allscor).value("Word").toString(),explains);
}
void En_Game::initdatabase()
{
     QSQLITE3_database *data;
     data=new QSQLITE3_database();
     data->init(filename);
     QStringList tablename;
     data->GetTableList(tablename);
     data->GetallData(tablename[0],word);
     delete data;
}
void En_Game::contextMenuEvent(QContextMenuEvent *event)
{
    pop_menu->clear();
    pop_menu->addAction(startgame);
    pop_menu->addAction(wordfile);
    pop_menu->addAction(learn);
    pop_menu->addAction(exam);
    pop_menu->addAction(usekeybord);
    pop_menu->exec(QCursor::pos());

    event->accept();

}
void En_Game::updatagame(QString en, QString ch)
{
    En=en;
    Ch=ch;
    createShapeItem();
    updataLetterSheet();
    update();
}
void En_Game::updataLetterSheet()
{
    createGameBaseLetter();
    for (int i=0;i<LettersKeybords.count();i++ )
    {
        LettersKeybords[i].setToolTip(GameBaseLetter.at(i));
    }
}
void En_Game::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    for (const En_Gameitem &shapeItem : qAsConst(LettersKeybords)) {
//! [8] //! [9]
        painter.translate(shapeItem.position());
//! [9] //! [10]
        painter.setBrush(shapeItem.color());
        painter.drawPath(shapeItem.path());
        QFont font = painter.font();
         font.setPixelSize(45);
         painter.setFont(font);
         const QRect rectangle = shapeItem.path().boundingRect().toRect();
         painter.drawText(rectangle, Qt::AlignHCenter|Qt::AlignTop, shapeItem.toolTip());
        painter.translate(-shapeItem.position());
    }
///////////////draw Ch
        painter.translate(Chpoint);
        QFont font = painter.font();
         font.setPixelSize(20);
         painter.setFont(font);
         painter.drawText(Chrectangle, Qt::AlignHCenter, Ch);
        painter.translate(-Chpoint);

/////////////////////scor
        painter.translate(scorPoint);
         font = painter.font();
         font.setPixelSize(25);
         painter.setFont(font);
         painter.drawText(scorrectangle, Qt::AlignHCenter|Qt::AlignVCenter,
                   "得分:"+QString::number(rightscor)+"/"+QString::number(allscor));
        painter.translate(-scorPoint);

/////////////////////
    for (const En_Gameitem &shapeItem : qAsConst(shapeItems)) {
//! [8] //! [9]
        painter.translate(shapeItem.position());
//! [9] //! [10]
        painter.setBrush(shapeItem.color());
        painter.drawPath(shapeItem.path());
        QFont font = painter.font();
         font.setPixelSize(45);
         painter.setFont(font);
         const QRect rectangle = shapeItem.path().boundingRect().toRect();
         painter.drawText(rectangle, Qt::AlignHCenter|Qt::AlignTop, shapeItem.toolTip());
        painter.translate(-shapeItem.position());
    }
}
void En_Game::isRight()
{
    QString a;
     for (int i=0;i<shapeItems.count() ; i++)
        a=a+shapeItems.at(i).toolTip();

     if(a==En)
         rightscor++;

     allscor++;

     gamestart();

}
void En_Game::mousePressEvent(QMouseEvent *event)
{

        int index=0;
        int temps=0;
    if(event->button() == Qt::LeftButton)
    {
      index= itemAt(event->pos());
        if (index > -1&&index<LettersKeybords.count()&&LettersKeybords[index].toolTip()!="?")
        {
            for (int i=0;i<shapeItems.count() ; i++)
            {
                if(shapeItems.at(i).toolTip()!="?")
                    continue;
                shapeItems[i].setToolTip(LettersKeybords.at(index).toolTip());
                shapeItems[i].setIndex(index);
                LettersKeybords[index].setToolTip("?");
                LettersKeybords[index].setIndex(i);
                update();
                 break;
            }

            for (int j=0;j<shapeItems.count() ; j++)
            {
                if(shapeItems.at(j).toolTip()=="?")
                    break;
                if(j==shapeItems.count()-1)
                    isRight();
            }

        }

       index = itemin(event->pos());
            if (index > -1 && index<shapeItems.count()&&shapeItems[index].toolTip()!="?")
            {
                temps=shapeItems.at(index).indexs();
                LettersKeybords[temps].setToolTip(shapeItems.at(index).toolTip());
                LettersKeybords[temps].setIndex(temps);
                shapeItems[index].setToolTip("?");
                shapeItems[index].setIndex(index);
                update();
                return;
            }



    }
}
int En_Game::itemAt(const QPoint &pos)
{
    for (int i = LettersKeybords.size() - 1; i >= 0; --i) {
        const En_Gameitem &item = LettersKeybords[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}
int En_Game::itemin(const QPoint &pos)
{
    for (int i = shapeItems.size() - 1; i >= 0; --i) {
        const En_Gameitem &item = shapeItems[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}
void En_Game::createShapeItem()
{

    int encount=En.count();
    shapeItems.resize(encount);
    if (encount>EnMaxCount)
        encount=EnMaxCount;
    QPoint starts=LetterStart+QPoint((6-encount/2)*50,0);
    for (int i=0;i<En.count();i++)
    {
            En_Gameitem item;
            item.setPosition(starts+QPoint(i*EachSize,0));
            item.setIndex(i);
            shapeItems[i]=item;
    }
}
void En_Game::createGameBaseLetter()
{
    QString a="qazwsxedcrfvtgbyhnujmiklop";
    int i=0;
    int index=0;
    for (int i=0;i<En.count() ;i++ )
    {
        index=QRandomGenerator::global()->bounded(0,25);
        a.insert(index,En.at(i));
    }

    for (i=0;i<14-En.count();i++)
    {
        index=QRandomGenerator::global()->bounded(0,En.count()+24);
        a.insert(index,a.at(i));
    }

    GameBaseLetter=a;
}
void En_Game::initLetterSheet()
{
    for (int i=0;i<EachRow;i++)
    {
        for(int j=0;j<EachCross;j++)
        {
            En_Gameitem item;
            item.setPosition(LetterSheet+QPoint(i*EachSize,j*EachSize));
            int b=i*EachCross+j;
            item.setIndex(b);
            item.setToolTip("?");
            LettersKeybords.append(item);
        }
    }
}
void En_Game::initLetter()
{
    int encount=5;
    QPoint starts=LetterStart+QPoint((6-encount/2)*50,0);
    for (int i=0;i<encount;i++)
    {
            En_Gameitem item;
            item.setPosition(starts+QPoint(i*EachSize,0));
            item.setIndex(i);
            shapeItems.append(item);
    }


}
