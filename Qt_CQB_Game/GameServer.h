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

	unsigned int refreshRate_HZ = 160;//服务器刷新率
	unsigned int pace = 160;//人物步速
	QTimer *timer;
	GameMap * map;
	std::vector<Player *> PlayerList;
	int newestPlayerId = -1;
	void addPlayer(Player * player);//添加玩家
	void getPlayerAction();//获取玩家行为
	void loadMap(GameMap * map);
	bool algo_CollisionDetection(double pos_x ,double pos_y,wall * wall);//碰撞检测算法(玩家-墙体)
	bool algo_CollisionDetection(Player * player, Player * player2);//碰撞检测算法(玩家-玩家)
protected:
	void run();

};