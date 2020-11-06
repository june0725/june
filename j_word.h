#ifndef J_WORD_H
#define J_WORD_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaPlayerControl>


#include <QAudioInput>

#include <QFile>

#include <QDebug>

#include <QTimer>

#include <QObject>

#include <QAudioOutput>

#include <iostream>

#include <QByteArray>

#include <QBuffer>


#include "sqlitedata.h"
namespace Ui {
class J_Word;
}
////////////////////////
///
///////jword stylefile
///     forms<<"id"<<"we"<<"wc"<<"wr"<<"pe"<<"pa"<<"ex"<<"tr";
//////formstyle<<"int"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT";
/// //////wr: 0 没学习的，1已经学习的且正确记忆的，2已学习但没正确记忆的，超过2的是多少次复习也没记住的
/// ///////////
/// ///////////////
///
///

enum filemodel{learn=1,add,exam,rewr};

class J_Word : public QDialog
{
    Q_OBJECT

public:
    explicit J_Word(QWidget *parent = nullptr);
    ~J_Word();
    void initdata(QString file,QString table);
    void NewJWord(QString file, QString table);
    void Setpadir(QString sounddir){pa=sounddir;}
    void Setpedir(QString sounddir){pe=sounddir;}
public slots:
void makeanswers();
void makewrong();
void makesoundA();
void makesoundE();
void makeup();
void makedown();
void cmdrun();

protected:
 void uishow();
 void rewrite();
 void addnew();
 void addwrong();
 void clearnwrong();

QString filename;
QString tablename;
QStringList forms;
QStringList formstyle;
QMap<QString,QString> formstyles;
QList<QSqlRecord> recorddata;
    Ui::J_Word *ui;
QMediaPlayer *playsound;
QString pa;
QString pe;
    int num;
    int rightnum;
    int maxnum;
    filemodel fm;



//        QAudio::Mode        m_mode;
//       QAudioFormat        format;
//       QAudioDeviceInfo    m_audioOutputDevice;
//       QAudioOutput*       m_audioOutput;
//       qint64              m_playPosition;
//       QBuffer             m_audioOutputIODevice;
//       QByteArray          m_buffer;


};

#endif // J_WORD_H
