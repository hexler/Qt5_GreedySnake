#ifndef GREEDYSNAKE_H
#define GREEDYSNAKE_H
#include "common.h"
#include "aboutlayout.h"
#include "herolist.h"
class GreedySnake : public QMainWindow
{
    Q_OBJECT
public:
    GreedySnake(QWidget *parent = nullptr);
    ~GreedySnake();
    QAction *easy_action;
    QAction *just_action;
    QAction *difficulty_action;
    QAction *smallM_map_action;
    QAction *medium_map_action;
    QAction *big_map_action;
    QAction *heros_action;
    QAction *music_on;
    QAction *music_off;
    QAction *about_help;
    QAction *about_game;
    void create_action();//主窗口的菜单栏的布局
    QSound *move_sound;
    QSound *eta_sound;
    QSound *fail_sound;
    QLabel *map_show;
    QLabel *mode_show;
    QLabel *music_show;
    QLabel *score_show;
    int sound_col;//记录音乐开关状态
    int timer_value;//记录定时器的定时数值
    QSettings *settings;
    void saveSettings();//将程序数据保存
    void loadSettings();//加载程序数据
    void drawBody(int x, int y,int mode=1);//画身体有关的函数
    void drawObstacle();//添加障碍物
    void drawFood();//添加食物
    void moveBody(int flag);//移动身体处理函数
    void clearMap();//清除地图
public slots:
    void handle();//定时器处理刷新函数
    void slot_hero_list();//展示游戏排行榜
    void slot_game_help();//打开游戏帮助消息框
    void slot_game_about();//游戏关于信息
    void slot_stageGroup(QAction *opt);//菜单按钮处理函数
    void slot_mapGroup(QAction *opt);
    void slot_stageMusic(QAction *opt);
private:
    void gameViewSize();//准备游戏画面
    void initGame();//准备游戏开始的初始化
    void game_over();//游戏结束
    void keyPressEvent(QKeyEvent *event);//获取输入并执行相应操作
    void closeEvent(QCloseEvent *e);//关闭事件
    QGraphicsEllipseItem *food;//食物指针
    QGraphicsScene *map;
    QGraphicsView *view;
    HeroList *hero_list;//排行榜类指针
    QTimer *timer;//定时器指针
    int display_W,display_H;//当前游戏窗口的大小数据
    int x,y,Dir_flag,Body_len,alive;//初始化的一些数据
    QList<QGraphicsItem *> sBody_list;//保存蛇身的容器
    QList<QGraphicsItem *> obstacle_list;//保存障碍物的容器
};
#endif // GREEDYSNAKE_H
