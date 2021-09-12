#include "greedysnake.h"

GreedySnake::GreedySnake(QWidget *parent) : QMainWindow(parent),map(new QGraphicsScene(this)),view(new QGraphicsView(map,this))
{
    this->setWindowIcon(QIcon("://1.png"));
    this->setWindowTitle(tr("贪吃蛇"));
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    move_sound = new QSound("://sound/click.wav",this);
    eta_sound = new QSound("://sound/question.wav",this);
    fail_sound = new QSound("://sound/youfail.wav",this);//用了声音之后 程序每次退出会返回 QCoreApplication::postEvent: Unexpected null receiver
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handle()));
    settings = new QSettings("settingsGui.ini",QSettings::IniFormat,this);
    hero_list=new HeroList;
    this->loadSettings();   //加载应用程序数据
    create_action();
    gameViewSize();
    timer->start(timer_value);//设置定时器
}
GreedySnake::~GreedySnake()
{
}
void GreedySnake::create_action()
{
    easy_action = new QAction(tr("简单"),this);
    easy_action->setCheckable(true);
    just_action = new QAction(tr("普通"),this);
    just_action->setCheckable(true);
    difficulty_action = new QAction(tr("困难"),this);
    difficulty_action->setCheckable(true);
    if(timer_value==200){easy_action->setChecked(true);}
    else if(timer_value==150){just_action->setChecked(true);}
    else{difficulty_action->setChecked(true);}
    smallM_map_action = new QAction(tr("小地图"),this);
    smallM_map_action->setCheckable(true);
    medium_map_action = new QAction(tr("中地图"),this);
    medium_map_action->setCheckable(true);
    big_map_action = new QAction(tr("大地图"),this);
    big_map_action->setCheckable(true);
    if(display_W==400){smallM_map_action->setChecked(true);}
    else if(display_W==600){medium_map_action->setChecked(true);}
    else{big_map_action->setChecked(true);}
    heros_action=new QAction(tr("排行榜"),this);
    music_on = new QAction(tr("音乐/开"),this);
    music_on->setCheckable(true);
    music_off = new QAction(tr("音乐/关"),this);
    music_off->setCheckable(true);
    if(sound_col){music_on->setChecked(true);}
    else{music_off->setChecked(true);}
    about_help = new QAction(tr("游戏帮助"),this);
    about_game = new QAction(tr("关于游戏"),this);
    QActionGroup *stageGroup = new QActionGroup(this);
    stageGroup->addAction(easy_action);
    stageGroup->addAction(just_action);
    stageGroup->addAction(difficulty_action);
    QActionGroup *mapGroup = new QActionGroup(this);
    mapGroup->addAction(smallM_map_action);
    mapGroup->addAction(medium_map_action);
    mapGroup->addAction(big_map_action);
    QActionGroup *musicGroup = new QActionGroup(this);
    musicGroup->addAction(music_off);
    musicGroup->addAction(music_on);
    QMenuBar *mbr = this->menuBar();
    QMenu *game_menu = mbr->addMenu(tr("菜 单"));
    QMenu *about_menu = mbr->addMenu(tr("帮 助"));
    game_menu->addAction(easy_action);
    game_menu->addAction(just_action);
    game_menu->addAction(difficulty_action);
    game_menu->addSeparator();
    game_menu->addAction(heros_action);
    game_menu->addSeparator();
    game_menu->addAction(smallM_map_action);
    game_menu->addAction(medium_map_action);
    game_menu->addAction(big_map_action);
    game_menu->addSeparator();
    game_menu->addAction(music_on);
    game_menu->addAction(music_off);
    about_menu->addAction(about_help);
    about_menu->addAction(about_game);
    QStatusBar *statusBar = this->statusBar();
    QString mapstat="  地图:";
    if(display_W==400) mapstat+="小地图 ";
    else if(display_W==600) mapstat+="中地图 ";
    else if(display_W==800) mapstat+="大地图 ";
    QString modestat="   难度:";
    if(timer_value==100) modestat+="困难 ";
    else if(timer_value==150) modestat+="普通 ";
    else if(timer_value==200) modestat+="简单 ";
    QString musicstat="   音乐:";
    if(sound_col==0){musicstat+="关 ";}
    else{musicstat+="开 ";}
    map_show=new QLabel(mapstat);
    mode_show=new QLabel(modestat);
    music_show=new QLabel(musicstat);
    score_show=new QLabel("\t得分:0");
    statusBar->addWidget(map_show);
    statusBar->addWidget(mode_show);
    statusBar->addWidget(music_show);
    statusBar->addPermanentWidget(score_show);
    this->connect(stageGroup,SIGNAL(triggered(QAction *)),this,SLOT(slot_stageGroup(QAction *)));//菜单栏 信号槽 处理
    this->connect(mapGroup,SIGNAL(triggered(QAction *)),this,SLOT(slot_mapGroup(QAction *)));
    this->connect(musicGroup,SIGNAL(triggered(QAction *)),this,SLOT(slot_stageMusic(QAction *)));
    this->connect(about_help,SIGNAL(triggered(bool)),this,SLOT(slot_game_help()));
    this->connect(about_game,SIGNAL(triggered(bool)),this,SLOT(slot_game_about()));
    this->connect(heros_action,SIGNAL(triggered(bool)),this,SLOT(slot_hero_list()));
}
void GreedySnake::saveSettings()
{
    settings->beginGroup("posSize");
    settings->setValue("pos",this->frameGeometry().topLeft());
    settings->setValue("x",display_W);
    settings->setValue("y",display_H);
    settings->endGroup();
    settings->beginGroup("playlevel");
    settings->setValue("timer_value",timer_value);
    settings->endGroup();
    settings->beginGroup("Music");
    settings->setValue("sound_col",sound_col);
    settings->endGroup();
}
void GreedySnake::loadSettings()
{
    settings->beginGroup("posSize");
    QPoint pos = settings->value("pos",QPoint(600,300)).toPoint();
    display_W=settings->value("x",600).toInt();
    display_H=settings->value("y",300).toInt();
    settings->endGroup();
    this->move(pos);
    this->resize(QSize(display_W,display_H));
    settings->beginGroup("playlevel");
    timer_value=settings->value("timer_value",200).toInt();
    settings->endGroup();
    settings->beginGroup("Music");
    sound_col=settings->value("sound_col",0).toInt();
    settings->endGroup();
}
void GreedySnake::drawBody(int x, int y,int mode)
{
    QGraphicsRectItem  *pItem = new QGraphicsRectItem();
    sBody_list.append(pItem);//将新建的item添加到容器当中
    QPen pen = pItem->pen();
    pen.setWidth(0);
    pen.setColor(Qt::white);
    pItem->setPen(pen);
    if(mode==DRAW_RED)
    {pItem->setBrush(QBrush(Qt::red));}
    else{pItem->setBrush(QBrush(Qt::green));}
    pItem->setRect(QRectF((x-1)*20+GRID_SIZE+1,(y-1)*20+GRID_SIZE+1,GRID_SIZE-2,GRID_SIZE-2 ));
    map->addItem(pItem);
}
void GreedySnake::drawObstacle()
{
    qsrand(QDateTime::currentDateTime().time().msec()+17);
    QList<QGraphicsItem *>::Iterator it;//迭代器用来遍历容器
    QGraphicsRectItem *pItem = new QGraphicsRectItem();
    obstacle_list.append(pItem);
    QPen pen = pItem->pen();
    pen.setWidth(0);
    pen.setColor(Qt::white);
    pItem->setPen(pen);
    pItem->setBrush(QBrush(Qt::black));
    int x=qrand()%(display_W/20-2)+1;//随机数字 生成
    int y=qrand()%(display_H/20-2)+1;
    pItem->setRect(QRectF((x-1)*20+GRID_SIZE+1,(y-1)*20+GRID_SIZE+1,GRID_SIZE-2,GRID_SIZE-2 ));
    map->addItem(pItem);
    for(it = sBody_list.begin(); it != sBody_list.end(); it++)//开始判断是否重叠
    {
        if(pItem->collidesWithItem(*it,Qt::IntersectsItemShape))
        {
            map->removeItem(pItem);//把障碍从场景当中移去
            delete  pItem;
            obstacle_list.removeLast();
            pItem=NULL;
            drawObstacle();
            break;
        }
    }
    if(pItem!=NULL)
    {
        if(pItem->collidesWithItem(food,Qt::IntersectsItemShape))
        {
            map->removeItem(pItem);//把障碍从场景当中移去
            delete  pItem;
            pItem=NULL;
            obstacle_list.removeLast();
            drawObstacle();
        }
    }
}
void GreedySnake::drawFood()
{
    qsrand(QDateTime::currentDateTime().time().msec());
    QList<QGraphicsItem *>::Iterator it;//迭代器用来遍历容器
    QGraphicsEllipseItem *pItem = new QGraphicsEllipseItem ();
    food=pItem;
    QPen pen = pItem->pen();
    pen.setWidth(0);
    pen.setColor(Qt::white);
    pItem->setPen(pen);
    pItem->setBrush(QBrush(Qt::blue));
    int x=qrand()%(display_W/20-2)+1;//随机数字 生成
    int y=qrand()%(display_H/20-2)+1;
    pItem->setRect(QRectF((x-1)*20+GRID_SIZE+1,(y-1)*20+GRID_SIZE+1,GRID_SIZE-2,GRID_SIZE-2 ));
    map->addItem(pItem);
    for(it = sBody_list.begin(); it != sBody_list.end(); it++)
    {
        if(food->collidesWithItem(*it,Qt::IntersectsItemShape))
        {
            map->removeItem(food);//把食物从场景当中移去
            delete  food;
            food=NULL;
            drawFood();
            break;
        }
    }
    for(it = obstacle_list.begin(); it != obstacle_list.end(); it++)
    {
        if(food->collidesWithItem(*it,Qt::IntersectsItemShape))
        {
            map->removeItem(food);//把食物从场景当中移去
            delete  food;
            food=NULL;
            drawFood();
            break;
        }
    }
}
void GreedySnake::moveBody(int flag)
{
    Dir_flag=flag;
    QGraphicsItem *temp;
    QList<QGraphicsItem *>::Iterator it;//迭代器用来遍历容器
    switch(flag)
    {
    case MOVE_KEEP: break;
    case MOVE_UP: --y; break;
    case MOVE_DOWN: ++y; break;
    case MOVE_LEFT: --x; break;
    case MOVE_RIGHT: ++x; break;
    }
    if(x<1||x>display_W/20-2||y<1||y>display_H/20-2)//之前是先绘制再判断 为了视图居中 先判断再绘图
    {
        alive=0;
        timer->stop();
        if(x<1) x=1;
        if(x>display_W/20-2) x=display_W/20-2;
        if(y<1) y=1;
        if(y>display_H/20-2) y=display_H/20-2;
        drawBody(x,y,DRAW_RED);
        if(sound_col){fail_sound->play();}
        game_over();
        return;
    }
    if(flag)
    {
        if(sound_col){ move_sound->play();}
        drawBody(x,y);//绘制身体
    }
    if(flag!=MOVE_KEEP && alive==1)
    {
        if((*(it= sBody_list.end()-1))->collidesWithItem(food,Qt::IntersectsItemShape))//这是 是否 吃到食物的判断
        {
            Body_len++;//蛇的身体加一
            score_show->setText("\t得分:"+QString::number(Body_len));
            if(sound_col){eta_sound->play();}
            map->removeItem(food);//把食物从场景当中移去
            delete  food;
            food=NULL;
            drawFood();
            if(Body_len%3==0) drawObstacle();//每获得三分 随机生成一块障碍物
        }
        else//没有吃到就删除蛇尾
        {
            it = sBody_list.begin();
            map->removeItem(*it);//场景当中移去
            temp=*it;
            delete temp;//删除掉item
            sBody_list.removeFirst();//从容器当中删除掉item
        }
    }
    for(it = sBody_list.begin(); it != sBody_list.end()-1; it++)//检测撞到自身死亡
    {
        if((*(sBody_list.end()-1))->collidesWithItem(*it,Qt::IntersectsItemShape))
        {
            alive=0;
            if(sound_col){fail_sound->play();}
            drawBody(x,y,DRAW_RED);
            timer->stop();
            game_over();
            break;
        }
    }
    for(it = obstacle_list.begin(); it != obstacle_list.end(); it++)//检测撞到障碍物死亡
    {
        if((*(sBody_list.end()-1))->collidesWithItem(*it,Qt::IntersectsItemShape))
        {
            alive=0;
            if(sound_col){fail_sound->play();}
            drawBody(x,y,DRAW_RED);
            timer->stop();
            game_over();
            break;
        }
    }
    view->show();
}
void GreedySnake::clearMap()//每次开始新的一句游戏之前 必要做的清理
{
    QList<QGraphicsItem *>::Iterator it;
    QList<QGraphicsItem *> item_list = map->items();
    QGraphicsItem *item = NULL;
    for(it = item_list.begin(); it != item_list.end(); it++)
    {
        item = *it;
        map->removeItem(*it);
        delete item;
    }
    for(it = sBody_list.begin(); it != sBody_list.end(); it++)
    {
        sBody_list.removeFirst();
    }
    for(it = obstacle_list.begin(); it != obstacle_list.end(); it++)
    {
        obstacle_list.removeFirst();
    }
}
void GreedySnake::gameViewSize()
{
    score_show->setText("\t得分:0");
    this->setFixedSize(display_W,display_H+40);//这个是固定窗口大小的
    map->clear();
    delete map;
    map=new QGraphicsScene(this);
    view->setScene(map);
    resize(display_W,display_H+40);
    setCentralWidget(view);
    QPen pen;//定义画笔，设置画笔颜色和宽度
    pen.setColor((Qt::black));
    pen.setWidth(1);
    for(int i=0;i<display_H/20-1;i++)
    {
        map->addLine(20,20*i+20,display_W-20,i*20+20,pen);
    }
    for(int j=0;j<display_W/20-1;j++)
    {
        map->addLine(20*j+20,20,20*j+20,display_H-20,pen);
    }
    initGame();
}
void GreedySnake::handle()
{
    this->setFocus();//锁定不了就每次都设置
    moveBody(Dir_flag);
}
void GreedySnake::game_over()
{
    int mode;
    if(timer_value==100){mode=0;}
    if(timer_value==150){mode=1;}
    if(timer_value==200){mode=2;}
    if(hero_list->readheros(Body_len,mode))
    {
        bool ok;
        QString name = QInputDialog::getText(this, tr("恭喜！"),tr("达到新纪录 请留下大名:"), QLineEdit::Normal,"你的名字",&ok,Qt::MSWindowsFixedSizeDialogHint);
        hero_list->saveheros(display_W,name,Body_len,mode);
        clearMap();
        timer->stop();
        gameViewSize();//保存用户信息之后 开始下一次游戏
        timer->start();
    }
    else
    {
        if(QMessageBox::question(this,tr("游戏结束"),tr("你的分数为:")+QString::number(Body_len)+tr("分 再来一把？"),QMessageBox::Yes,QMessageBox::No )==QMessageBox::Yes)
        {
            clearMap();
            timer->stop();
            gameViewSize();
            timer->start();
        }
        else
        {/*点击否的话 可能代表不想玩了 询问是否退出程序*/}
    }
}
void GreedySnake::slot_hero_list()
{
    HeroList w;
    w.exec();
}
void GreedySnake::slot_stageGroup(QAction *opt)
{
    if(alive)
    {
        if(opt==easy_action)
        {timer->start(timer_value=200);mode_show->setText("   难度:简单 ");}
        else if(opt==just_action)
        {timer->start(timer_value=150);mode_show->setText("   难度:普通 ");}
        else
        {timer->start(timer_value=100);mode_show->setText("   难度:困难 ");}
    }
    else
    {
        clearMap();
        if(opt==easy_action)
        {timer->start(timer_value=200);mode_show->setText("   难度:简单 ");}
        else if(opt==just_action)
        {timer->start(timer_value=150);mode_show->setText("   难度:普通 ");}
        else
        {timer->start(timer_value=100);mode_show->setText("   难度:困难 ");}
        gameViewSize();//重新开始游戏
    }
}
void GreedySnake::slot_mapGroup(QAction *opt)
{
    clearMap();
    timer->stop();
    if(opt==smallM_map_action)
    {display_W=400,display_H=240;map_show->setText("  地图:小地图 ");}
    else if(opt==medium_map_action)
    {display_W=600,display_H=300;map_show->setText("  地图:中地图 ");}
    else if(opt==big_map_action)
    {display_W=800,display_H=480;map_show->setText("  地图:大地图 ");}
    gameViewSize();
    timer->start();
}
void GreedySnake::slot_stageMusic(QAction *opt)
{
    if(opt==music_on){sound_col=1;music_show->setText("   音乐:开 ");}
    else if(opt==music_off){sound_col=0;music_show->setText("   音乐:关 ");}
}
void GreedySnake::slot_game_help()
{
    QMessageBox::information(this,tr("游戏帮助"),tr("1.键盘方向键控制蛇进行移动\n2.左上角菜单进行游戏设定\n3.长按空格可以加速\n4.每得三分就会随机出现一个障碍物\n"),QMessageBox::Ok);
}
void GreedySnake::slot_game_about()
{
    aboutLayout w;
    w.exec();
}

void GreedySnake::initGame()
{
    QPixmap bg(GRID_SIZE,GRID_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0,0,GRID_SIZE,GRID_SIZE);
    p.setPen(Qt::blue);
    x=7,y=5;
    Dir_flag=0;//默认方向为0 不动
    Body_len=0;//长度为4 分数为0
    alive=1;//活着
    drawBody(5,5);
    drawBody(6,5);
    drawBody(7,5);
    drawFood();
    view->show();//视图更新
}
void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    {QCoreApplication::processEvents(QEventLoop::AllEvents, 100);}
}
void GreedySnake::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)//根据按键执行相应的函数
    {
        this->close();//结束游戏 后期给一个暂停窗口
    }
    if(event->key()==Qt::Key_Space)
    {
        if(alive)
        {
            moveBody(Dir_flag);
            sleep(100);
        }
    }
    if(event->key()==Qt::Key_Up){Dir_flag=MOVE_UP;}
    if(event->key()==Qt::Key_Down){Dir_flag=MOVE_DOWN;}
    if(event->key()==Qt::Key_Left){Dir_flag=MOVE_LEFT;}
    if(event->key()==Qt::Key_Right){Dir_flag=MOVE_RIGHT;}
    if(event->key()==Qt::Key_0){moveBody(MOVE_RIGHT);}
    view->show();
}
void GreedySnake::closeEvent(QCloseEvent *e)//按下关闭按钮之后 触发关闭事件
{
    timer->stop();//关闭事件 可以 直接关闭定时器
    if(QMessageBox::question(this,tr("退出"),tr("确定要退出游戏吗？"),QMessageBox::Yes,QMessageBox::No )==QMessageBox::Yes)
    {
        this->saveSettings();
        e->accept();//不会将事件传递给组件的父组件
    }
    else if(alive)//如果玩家还没有死的话 需要重新启动定时器
    {
        e->ignore();
        timer->start();
    }
    else//点击否 忽略掉
    {
        e->ignore();
    }
}
