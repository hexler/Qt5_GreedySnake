#ifndef HEROLIST_H
#define HEROLIST_H
#include <QWidget>
#include <QSettings>
#include <QDebug>
#include <QLabel>
#include <QIcon>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
class HeroList : public QDialog
{
    Q_OBJECT
public:
    explicit HeroList(QWidget *parent = nullptr);
    QString easy_name1;
    int easy_score1;
    QString easy_mode1;
    QString easy_name2;
    int easy_score2;
    QString easy_mode2;
    QString easy_name3;
    int easy_score3;
    QString easy_mode3;
    QString medium_name1;
    int medium_score1;
    QString medium_mode1;
    QString medium_name2;
    int medium_score2;
    QString medium_mode2;
    QString medium_name3;
    int medium_score3;
    QString medium_mode3;
    QString diff_name1;
    int diff_score1;
    QString diff_mode1;
    QString diff_name2;
    int diff_score2;
    QString diff_mode2;
    QString diff_name3;
    int diff_score3;
    QString diff_mode3;
    QSettings *heros;
    int readheros(int score,int mode);    //将读取程序数据进行判断
    void saveheros(int display_W,QString name,int score,int mode);//保存排行榜信息
    void loadheros();    //从文件读取排行榜信息
};
#endif // HEROLIST_H
