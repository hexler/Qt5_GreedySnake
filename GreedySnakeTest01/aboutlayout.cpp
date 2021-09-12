#include "aboutlayout.h"

aboutLayout::aboutLayout(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("关于游戏");
    this->setWindowIcon(QIcon("://1.png"));
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(380,200);
    QLabel *head=new QLabel;
    head->setPixmap(QPixmap("://1.png"));
    QLabel *text1=new QLabel("贪吃蛇1.7");
    QLabel *text2=new QLabel("Author:Hexler");
    QLabel *text3=new QLabel("Acknowledge:");
    QLabel *text4=new QLabel("Qt Creator 4.11.0");
    QLabel *text5=new QLabel("Qt_5_9_9_MinGW_32bit");
    QLabel *test6=new QLabel();
    test6->setOpenExternalLinks(true);
    test6->setText("<a style='color:red;' href=\"https://weibo.com/hexler\">作者weibo:@Hexler");
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(head);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addStretch(0);
    vlayout->addWidget(text1);
    vlayout->addWidget(text2);
    vlayout->addWidget(text3);
    vlayout->addWidget(text4);
    vlayout->addWidget(text5);
    vlayout->addWidget(test6);
    vlayout->addStretch(0);
    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->addLayout(hlayout);
    mainlayout->addLayout(vlayout);
    qDebug()<<"test 已执行关于游戏构造函数";
}
