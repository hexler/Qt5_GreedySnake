#include "herolist.h"

HeroList::HeroList(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("玩家排行榜:");
    this->setWindowIcon(QIcon("://1.png"));
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(600,300);
    QLabel *head=new QLabel;
    head->setPixmap(QPixmap("://1.png"));
    this->loadheros();//从文件读取用户排行信息
    QLabel *text1=new QLabel("难度:简单");
    QLabel *text2=new QLabel("用户名:"+easy_name1+"\t得分:"+QString::number(easy_score1)+"\t地图:"+easy_mode1);
    QLabel *text3=new QLabel("用户名:"+easy_name2+"\t得分:"+QString::number(easy_score2)+"\t地图:"+easy_mode2);
    QLabel *text4=new QLabel("用户名:"+easy_name3+"\t得分:"+QString::number(easy_score3)+"\t地图:"+easy_mode3);
    QLabel *text5=new QLabel("难度:普通");
    QLabel *text6=new QLabel("用户名:"+medium_name1+"\t得分:"+QString::number(medium_score1)+"\t地图:"+medium_mode1);
    QLabel *text7=new QLabel("用户名:"+medium_name2+"\t得分:"+QString::number(medium_score2)+"\t地图:"+medium_mode2);
    QLabel *text8=new QLabel("用户名:"+medium_name3+"\t得分:"+QString::number(medium_score3)+"\t地图:"+medium_mode3);
    QLabel *text9=new QLabel("难度:困难");
    QLabel *text10=new QLabel("用户名:"+diff_name1+"\t得分:"+QString::number(diff_score1)+"\t地图:"+diff_mode1);
    QLabel *text11=new QLabel("用户名:"+diff_name2+"\t得分:"+QString::number(diff_score2)+"\t地图:"+diff_mode2);
    QLabel *text12=new QLabel("用户名:"+diff_name3+"\t得分:"+QString::number(diff_score3)+"\t地图:"+diff_mode3);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(head);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addStretch(0);
    vlayout->addWidget(text1);
    vlayout->addWidget(text2);
    vlayout->addWidget(text3);
    vlayout->addWidget(text4);
    vlayout->addWidget(text5);
    vlayout->addWidget(text6);
    vlayout->addWidget(text7);
    vlayout->addWidget(text8);
    vlayout->addWidget(text9);
    vlayout->addWidget(text10);
    vlayout->addWidget(text11);
    vlayout->addWidget(text12);
    vlayout->addStretch(0);
    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->addLayout(hlayout);
    mainlayout->addLayout(vlayout);
}
int HeroList::readheros(int score,int mode)   //判断程序
{
    loadheros();//如果玩家不打开排行榜的情况 我们需要手动读取数据
    if(mode==2)//简单难度
    {
        if(easy_score3<score)
        {
            return 1;
        }
    }
    else if(mode==1)//普通难度
    {
        if(medium_score3<score)
        {
            return 1;
        }
    }
    else if(mode==0)//困难难度
    {
        if(diff_score3<score)
        {
            return 1;
        }
    }
    return 0;
}
void HeroList::saveheros(int display_W, QString name, int score,int mode)
{
    heros = new QSettings("gamedatalist.ini",QSettings::IniFormat,this);
    if(name.isEmpty())
    {
        name="无名氏";
    }
    heros->beginGroup("gameUserData");
    QString modestr="";
    if(display_W==400)
    {
        modestr="小地图";
    }
    else if(display_W==600)
    {
        modestr="中地图";
    }
    else if(display_W==800)
    {
        modestr="大地图";
    }
    if(mode==2)//简单难度
    {
        if(easy_score2<score)//判断是不是大于第二名
        {
            if(easy_score1<score)//判断是不是大于第一名
            {
                heros->setValue("easy_name3",easy_name2);//第二名的数据给第三名
                heros->setValue("easy_score3",easy_score2);
                heros->setValue("easy_mode3",easy_mode2);
                heros->setValue("easy_name2",easy_name1);//第一名的数据给第二名
                heros->setValue("easy_score2",easy_score1);
                heros->setValue("easy_mode2",easy_mode1);
                heros->setValue("easy_name1",name);//当前数据给第二名
                heros->setValue("easy_score1",score);
                heros->setValue("easy_mode1",modestr);
            }
            else//不大于第一名就是第二名
            {
                heros->setValue("easy_name3",easy_name2);//第二名的数据给第三名
                heros->setValue("easy_score3",easy_score2);
                heros->setValue("easy_mode3",easy_mode2);
                heros->setValue("easy_name2",name);//当前数据给第二名
                heros->setValue("easy_score2",score);
                heros->setValue("easy_mode2",modestr);
            }
        }
        else//不大于第二名那就是第三名
        {
            heros->setValue("easy_name3",name);
            heros->setValue("easy_score3",score);
            heros->setValue("easy_mode3",modestr);
        }
    }
    else if(mode==1)//普通难度
    {
        if(medium_score2<score)//判断是不是大于第二名
        {
            if(medium_score1<score)//判断是不是大于第一名
            {
                heros->setValue("medium_name3",medium_name2);//第二名的数据给第三名
                heros->setValue("medium_score3",medium_score2);
                heros->setValue("medium_mode3",medium_mode2);
                heros->setValue("medium_name2",medium_name1);//第一名的数据给第二名
                heros->setValue("medium_score2",medium_score1);
                heros->setValue("medium_mode2",medium_mode1);
                heros->setValue("medium_name1",name);//当前数据给第二名
                heros->setValue("medium_score1",score);
                heros->setValue("medium_mode1",modestr);
            }
            else//不大于第一名就是第二名
            {
                heros->setValue("medium_name3",medium_name2);//第二名的数据给第三名
                heros->setValue("medium_score3",medium_score2);
                heros->setValue("medium_mode3",medium_mode2);
                heros->setValue("medium_name2",name);//当前数据给第二名
                heros->setValue("medium_score2",score);
                heros->setValue("medium_mode2",modestr);
            }
        }
        else//不大于第二名那就是第三名
        {
            heros->setValue("medium_name3",name);
            heros->setValue("medium_score3",score);
            heros->setValue("medium_mode3",modestr);
        }
    }
    else if(mode==0)//困难难度
    {
        if(diff_score2<score)//判断是不是大于第二名
        {
            if(diff_score1<score)//判断是不是大于第一名
            {
                heros->setValue("diff_name3",diff_name2);//第二名的数据给第三名
                heros->setValue("diff_score3",diff_score2);
                heros->setValue("diff_mode3",diff_mode2);
                heros->setValue("diff_name2",diff_name1);//第一名的数据给第二名
                heros->setValue("diff_score2",diff_score1);
                heros->setValue("diff_mode2",diff_mode1);
                heros->setValue("diff_name1",name);//当前数据给第二名
                heros->setValue("diff_score1",score);
                heros->setValue("diff_mode1",modestr);
            }
            else//不大于第一名就是第二名
            {
                heros->setValue("diff_name3",diff_name2);//第二名的数据给第三名
                heros->setValue("diff_score3",diff_score2);
                heros->setValue("diff_mode3",diff_mode2);
                heros->setValue("diff_name2",name);//当前数据给第二名
                heros->setValue("diff_score2",score);
                heros->setValue("diff_mode2",modestr);
            }
        }
        else//不大于第二名那就是第三名
        {
            heros->setValue("diff_name3",name);
            heros->setValue("diff_score3",score);
            heros->setValue("diff_mode3",modestr);
        }
    }
    heros->endGroup();
}
void HeroList::loadheros()    //加载程序数据
{
    heros = new QSettings("gamedatalist.ini",QSettings::IniFormat,this);
    heros->beginGroup("gameUserData");
    easy_name1 = heros->value("easy_name1","xxx").toString();
    easy_score1 = heros->value("easy_score1",0).toInt();
    easy_mode1 = heros->value("easy_mode1","xxx").toString();
    easy_name2 = heros->value("easy_name2","xxx").toString();
    easy_score2 = heros->value("easy_score2",0).toInt();
    easy_mode2 = heros->value("easy_mode2","xxx").toString();
    easy_name3 = heros->value("easy_name3","xxx").toString();
    easy_score3 = heros->value("easy_score3",0).toInt();
    easy_mode3 = heros->value("easy_mode3","xxx").toString();
    medium_name1 = heros->value("medium_name1","xxx").toString();
    medium_score1 = heros->value("medium_score1",0).toInt();
    medium_mode1 = heros->value("medium_mode1","xxx").toString();
    medium_name2 = heros->value("medium_name2","xxx").toString();
    medium_score2 = heros->value("medium_score2",0).toInt();
    medium_mode2 = heros->value("medium_mode2","xxx").toString();
    medium_name3 = heros->value("medium_name3","xxx").toString();
    medium_score3 = heros->value("medium_score3",0).toInt();
    medium_mode3 = heros->value("medium_mode3","xxx").toString();
    diff_name1 = heros->value("diff_name1","xxx").toString();
    diff_score1 = heros->value("diff_score1",0).toInt();
    diff_mode1 = heros->value("diff_mode1","xxx").toString();
    diff_name2 = heros->value("diff_name2","xxx").toString();
    diff_score2 = heros->value("diff_score2",0).toInt();
    diff_mode2 = heros->value("diff_mode2","xxx").toString();
    diff_name3 = heros->value("diff_name3","xxx").toString();
    diff_score3 = heros->value("diff_score3",0).toInt();
    diff_mode3 = heros->value("diff_mode3","xxx").toString();
    heros->endGroup();
}

