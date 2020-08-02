#include "j_word.h"
#include "ui_j_word.h"

J_Word::J_Word(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::J_Word)
{
    ui->setupUi(this);
    forms<<"id"<<"we"<<"wc"<<"wr"<<"pe"<<"pa"<<"ex"<<"tr";
    formstyle<<"int"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT"<<"TEXT";
    for(int i=0;i<forms.count();i++)
        formstyles.insert(forms[i],formstyle[i]);
    fm=learn;///////
    pa=QDir::currentPath()+"/sound/An/";
    pe=QDir::currentPath()+"/sound/En/";
    playsound = new QMediaPlayer(this);
    playsound->setVolume(100);

}

J_Word::~J_Word()
{
    delete ui;
}
void J_Word::NewJWord(QString file,QString table)
{
    filename=file;
    tablename=table;
    QSQLITE3_database database;
    database.Newdatafile(filename,tablename,forms,formstyles);
    fm=add;
    initdata(file,table);
    uishow();
}
void J_Word::uishow()
{
    switch(fm)
    {
        case exam:
        ui->makeup->setEnabled(false);
        ui->makedown->setEnabled(false);
        ui->source->setText(recorddata[num].value("we").toString());
        ui->cmdline->setText(tr("成绩：")+QString::number(rightnum)+tr("/")+QString::number(maxnum));
        break;
    case add:
    case rewr:
        if(maxnum<=0)
        {
        ui->source->clear();
        ui->makewrong->setEnabled(false);
        fm=add;
        }
        ui->makeanswers->setText(tr("插入"));
        break;
    default:
        if(maxnum<=0)
        {
            ui->source->clear();
        }
        else
        {
        ui->source->setText(recorddata[num].value("we").toString());
        ui->pa->setText(recorddata[num].value("pa").toString());
        ui->pe->setText(recorddata[num].value("pe").toString());
        }
        break;
    }


}
void J_Word::initdata(QString file,QString table)
{
    filename=file;
    tablename=table;
    recorddata.clear();
    QSQLITE3_database database;
    database.init(filename);
    database.GetallData(tablename,recorddata);
    num=0;
    maxnum=recorddata.size();
    uishow();
}
void J_Word::makeanswers()
{
    switch(fm)
    {
        case exam:
        if(ui->source->toPlainText()==recorddata[num].value("we").toString()&&ui->target->toPlainText()==recorddata[num].value("wc").toString())
        {
            clearnwrong();
            rightnum=rightnum+1;
        }
        else
        {
            addwrong();
        }
            if(num==maxnum-1)
            {
                ui->makeanswers->setEnabled(false);
            }
            else
            {
            makedown();
            }
        break;
    case rewr:
        rewrite();
        break;
    case add:
        addnew();
        break;
    default:
        if(maxnum>0)
        {
        ui->source->setText(recorddata[num].value("we").toString());
        ui->target->setText(recorddata[num].value("wc").toString());
        ui->example->setText(recorddata[num].value("ex").toString());
        ui->pa->setText(recorddata[num].value("pa").toString());
        ui->pe->setText(recorddata[num].value("pe").toString());
        ui->translate->setText(recorddata[num].value("tr").toString());
        }
        else
        {

        }
        break;

    }



}
void J_Word::makewrong()
{
    recorddata.clear();
    QSQLITE3_database database;
    database.init(filename);
    QMap<QString,QString> f;
    f["wr"]="2";
    database.GetData(tablename,f,recorddata);
    num=0;
    rightnum=0;
    maxnum=recorddata.size();
    if(maxnum<=0)
    {
      ui->cmdline->setText(tr("未发现错题集!"));
      recorddata.clear();
      QSQLITE3_database database;
      database.init(filename);
      QMap<QString,QString> f;
      f["wr"]="0";
      database.GetData(tablename,f,recorddata);
      num=0;
      rightnum=0;
      maxnum=recorddata.size();
    }
    else
    {
    uishow();
    }
}
void J_Word::makesoundA()
{
    if(playsound->state()!=QMediaPlayer::StoppedState)
    playsound->stop();
    QString f=pa+recorddata[num].value("we").toString()+".mp3";
    if(QFileInfo::exists(f))
    {
      playsound->setMedia(QUrl::fromLocalFile(f));
        playsound->play();
    }



//        QFile file("/home/pdw/build-june-unknown-Debug/a.mp3");
//        file.open(QFile::ReadOnly);
//        m_buffer = file.readAll();
//        file.close();
//        m_audioOutputDevice=QAudioDeviceInfo::defaultOutputDevice();
//             format.setSampleRate(16000);
//             format.setChannelCount(1);
//             format.setSampleSize(16);
//             format.setCodec("mp3");
//             format.setByteOrder(QAudioFormat::LittleEndian);
//             format.setSampleType(QAudioFormat::SignedInt);
//            QStringList p=m_audioOutputDevice.supportedCodecs();
//             if (!m_audioOutputDevice.isFormatSupported(format)) {
//                     qWarning() << "Default format not supported - trying to use nearest";
//                     format = m_audioOutputDevice.nearestFormat(format);
//                 }

//           m_audioOutput = new QAudioOutput(m_audioOutputDevice, format);

//    if (m_audioOutput)
//    {
//           m_audioOutputIODevice.setBuffer(&m_buffer);
//           m_audioOutputIODevice.open(QIODevice::ReadOnly);
//           m_audioOutputIODevice.seek(0);
//           m_audioOutput->start(&m_audioOutputIODevice);
//    }

}
void J_Word::makesoundE()
{
    if(playsound->state()!=QMediaPlayer::StoppedState)
    playsound->stop();
    QString f=pe+recorddata[num].value("we").toString()+".mp3";
    if(QFileInfo::exists(f))
    {
      playsound->setMedia(QUrl::fromLocalFile(f));
        playsound->play();
    }

}
void J_Word::makedown()
{
    if(num+1<maxnum)
    {
        num=num+1;
    }
    else
    {
       num=maxnum-1;
       ui->makedown->setEnabled(false);
    }
    ui->makeup->setEnabled(true);
    ui->makeanswers->setEnabled(true);
     uishow();
}
void J_Word::makeup()
{
    if(num-1>=0)
        {
            num=num-1;
        }
    else
    {
         num=0;
         ui->makeup->setEnabled(false);
    }
    ui->makedown->setEnabled(true);
    ui->makeanswers->setEnabled(true);
     uishow();
}
void J_Word::cmdrun()
{
    QString cmd=ui->cmdline->text();

    if(cmd=="addnew")
    {
       fm=add;
       ui->makeanswers->setText(tr("插入"));
       ui->source->clear();
       return;
    }
    if(cmd=="rewrite")
    {
        fm=rewr;
        ui->makeanswers->setText(tr("更新"));
        uishow();
    return;
    }
    if(cmd=="exam")
    {
        fm=exam;
        rightnum=0;
        num=0;
        ui->makeanswers->setText(tr("提交"));
        ui->makewrong->setEnabled(false);
        uishow();
    return;
    }

    fm=learn;
    ui->makeanswers->setText(tr("答案"));
    uishow();
}
void J_Word::addnew()
{
    QString wr="0";
    QSQLITE3_database database;
    database.init(filename);
    QVariantList ls;
    if(maxnum<=0)
    {
    ls<<"1";
    }
    else
    {
        ls<<QString::number(recorddata[maxnum-1].value("id").toInt()+1);
    }
     ls<<ui->source->toPlainText()
    <<ui->target->toPlainText()
    <<wr
    <<ui->pe->toPlainText()
    <<ui->pa->toPlainText()
    <<ui->example->toPlainText()
    <<ui->translate->toPlainText();
    database.AddData(tablename,ls);
    recorddata.clear();
    database.GetallData(tablename,recorddata);
    maxnum=recorddata.size();
    uishow();
}
void J_Word::addwrong()
{
    QString wr="2";
    QSQLITE3_database database;
    database.init(filename);
    QVariantList ls;
    ls<<recorddata[num].value("id").toString()
        <<recorddata[num].value("we").toString()
          <<recorddata[num].value("wc").toString()
            <<wr
              <<recorddata[num].value("pe").toString()
                <<recorddata[num].value("pa").toString()
                      <<recorddata[num].value("ex").toString()
                        <<recorddata[num].value("tr").toString();
    database.UpData(tablename,ls);
    ui->makeanswers->setEnabled(false);
}
void J_Word::clearnwrong()
{
    QString wr="0";
    QSQLITE3_database database;
    database.init(filename);
    QVariantList ls;
    ls<<recorddata[num].value("id").toString()
        <<recorddata[num].value("we").toString()
          <<recorddata[num].value("wc").toString()
            <<wr
              <<recorddata[num].value("pe").toString()
                <<recorddata[num].value("pa").toString()
                      <<recorddata[num].value("ex").toString()
                        <<recorddata[num].value("tr").toString();
    database.UpData(tablename,ls);
    ui->makeanswers->setEnabled(false);
}
void J_Word::rewrite()
{
    QString wr="0";
    QSQLITE3_database database;
    database.init(filename);
    QVariantList ls;
    ls<<recorddata[num].value("id").toString()
      <<ui->source->toPlainText()
    <<ui->target->toPlainText()
    <<wr
    <<ui->pe->toPlainText()
    <<ui->pa->toPlainText()    
    <<ui->example->toPlainText()
    <<ui->translate->toPlainText();
    database.UpData(tablename,ls);
    recorddata.clear();
    database.GetallData(tablename,recorddata);
    uishow();
}
