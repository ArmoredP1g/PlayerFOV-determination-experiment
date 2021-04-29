#pragma once
#include <qthread.h>
#include "Player.h"
#include <vector>
#include <qtimer.h>
#include "map.h"
#include <qmath.h>

#define PLAYER_SIZE 10
//游戏后台判定
class GameServer : public QThread
{
	Q_OBJECT
public:
	GameServer(QObject *parent = NULL);
	~GameServer();

	unsigned int refreshRate_HZ = 60;//服务器刷新率
	unsigned int pace = 140;//人物步速
	QTimer *timer;
	GameMap * map;
	std::vector<Player *> PlayerList;//参与玩家列表
	Player playerVisualMap[12][12];//玩家间是否出现在对方视野内的图，玩家上限12个
	bool ObjectVisualMap[12][50];//物体是否出现在玩家视野里 物体上限50个
	int newestPlayerId = -1;
	void addPlayer(Player * player);//添加玩家
	void addDummyEnemyPlayers();//*测试用*添加假目标
	void getPlayerAction();//获取玩家行为
	void visualCalculate();//获取视野内其他玩家
	void loadMap(GameMap * map);
protected:
	void run();

};