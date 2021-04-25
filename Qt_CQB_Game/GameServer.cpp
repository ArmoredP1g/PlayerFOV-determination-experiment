#include"GameServer.h"
#include<iostream>
using namespace std;

GameServer::GameServer(QObject *parent)
{
	//配置服务器刷新频率
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout,this, &GameServer::run);
	timer->start(1000/refreshRate_HZ);
}

GameServer::~GameServer()
{

}

void GameServer::run()
{
	//获取玩家行为
	//calculate game events
	getPlayerAction();
}


 void GameServer::addPlayer(Player * player)
{
	//给玩家分配一个id
	player->player_id = ++newestPlayerId;
	player->pos_x = 20;
	player->pos_y = 20;
	PlayerList.push_back(player);
}

void GameServer::getPlayerAction()
{
	for (int players = 0; players < PlayerList.size(); players++)
	{
		//判断移动;
		//前
		if (PlayerList[players]->behavior_move_ahead)
		{
			//没碰撞检测
			PlayerList[players]->pos_y -= (pace / refreshRate_HZ);
		}
		//后
		if (PlayerList[players]->behavior_move_back)
		{
			//没碰撞检测
			PlayerList[players]->pos_y += (pace / refreshRate_HZ);
		}
		//left
		if (PlayerList[players]->behavior_move_left)
		{
			//没碰撞检测
			PlayerList[players]->pos_x -= (pace / refreshRate_HZ);
		}
		//right
		if (PlayerList[players]->behavior_move_right)
		{
			//没碰撞检测
			PlayerList[players]->pos_x += (pace / refreshRate_HZ);
		}
	}
}