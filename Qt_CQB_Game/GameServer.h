#pragma once
#include <qthread.h>
#include "Player.h"
#include <vector>
#include <qtimer.h>
#include "map.h"
//游戏后台判定
class GameServer : public QThread
{
	Q_OBJECT
public:
	GameServer(QObject *parent = NULL);
	~GameServer();

	unsigned int refreshRate_HZ = 30;//服务器刷新率
	unsigned int pace = 60;//人物步速
	QTimer *timer;
	std::vector<Player *> PlayerList;
	int newestPlayerId = -1;
	void addPlayer(Player * player);//添加玩家
	void getPlayerAction();//获取玩家行为
	bool algo_CollisionDetection(Player * player,wall * wall);//碰撞检测算法(玩家-墙体)
	bool algo_CollisionDetection(Player * player, Player * player2);//碰撞检测算法(玩家-玩家)
protected:
	void run();

};