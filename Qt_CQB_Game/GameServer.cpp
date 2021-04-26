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

void GameServer::loadMap(GameMap * map)
{
	this->map = map;
}

 void GameServer::addPlayer(Player * player)
{
	//给玩家分配一个id
	player->player_id = ++newestPlayerId;
	player->pos_x = 0;
	player->pos_y = 0;
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
			//进行碰撞检测
			bool CollisionDetected = false;
			for (int maps = 0; maps < map->walls.size(); maps++)
			{
				if (algo_CollisionDetection(PlayerList[players]->pos_x, PlayerList[players]->pos_y - (pace*(1+ PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ), &map->walls[maps]))
				{
					CollisionDetected = true;
					break;
				}
			}
			if (!CollisionDetected)
			{
				PlayerList[players]->pos_y -= (pace*(1 + PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ);
			}	
		}


		//后
		if (PlayerList[players]->behavior_move_back)
		{
			//进行碰撞检测
			bool CollisionDetected = false;
			for (int maps = 0; maps < map->walls.size(); maps++)
			{
				if (algo_CollisionDetection(PlayerList[players]->pos_x, PlayerList[players]->pos_y + (pace*(1 + PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ), &map->walls[maps]))
				{
					CollisionDetected = true;
					break;
				}
			}
			if (!CollisionDetected)
			{
				PlayerList[players]->pos_y += (pace*(1 + PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ);
			}	
		}


		//left
		if (PlayerList[players]->behavior_move_left)
		{
			//进行碰撞检测
			bool CollisionDetected = false;
			for (int maps = 0; maps < map->walls.size(); maps++)
			{
				if (algo_CollisionDetection(PlayerList[players]->pos_x-(pace*(1 + PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ), PlayerList[players]->pos_y, &map->walls[maps]))
				{
					CollisionDetected = true;
					break;
				}
			}
			if (!CollisionDetected) 
			{
				PlayerList[players]->pos_x -= (pace*(1 + PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ);
			}
			
		}
		//right
		if (PlayerList[players]->behavior_move_right)
		{
			//进行碰撞检测
			bool CollisionDetected = false;
			for (int maps = 0; maps < map->walls.size(); maps++)
			{
				if (algo_CollisionDetection(PlayerList[players]->pos_x + (pace*(1 + PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ), PlayerList[players]->pos_y, &map->walls[maps]))
				{
					CollisionDetected = true;
					break;
				}
			}
			if (!CollisionDetected)
			{
				PlayerList[players]->pos_x += (pace*(1 + PlayerList[players]->behavior_move_speedUp) / refreshRate_HZ);
			}			
		}
	}
}

//点与墙体的碰撞检测(两点式的点到直线距离公式)
bool GameServer::algo_CollisionDetection(double pos_x, double pos_y, wall * wall)
{
	//情况一、点在线端点+人物半径 形成的矩形范围外，一定不会发生碰撞
	double x_max,x_min,y_max,y_min;
	if (wall->startPoint.x() > wall->endPoint.x())
	{
		x_max = wall->startPoint.x();
		x_min = wall->endPoint.x();
	}
	else
	{
		x_min = wall->startPoint.x();
		x_max = wall->endPoint.x();
	}

	if (wall->startPoint.y() > wall->endPoint.y())
	{
		y_max = wall->startPoint.y();
		y_min = wall->endPoint.y();
	}
	else
	{
		y_min = wall->startPoint.y();
		y_max = wall->endPoint.y();
	}
	if (pos_x > x_max + PLAYER_SIZE || pos_x < x_min - PLAYER_SIZE || pos_y > y_max + PLAYER_SIZE || pos_y < y_min - PLAYER_SIZE)
	{
		return false;
	}
	//情况二、线段完全垂直，避免出现分母为0的情况，需要单独判断
	if (wall->startPoint.x() == wall->endPoint.x())
	{
		return true;//肯定碰撞了
	}
	//以上情况都不满足 正常求点到直线距离即可
	double dis = fabs(((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()))*pos_x - pos_y + wall->startPoint.y() - ((wall->endPoint.y() - wall->startPoint.y())*wall->startPoint.x()) / (wall->endPoint.x() - wall->startPoint.x()))
		/
		sqrt(pow((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()), 2) + 1);
	//cout << "人物与墙体距离:	" << dis << endl;
	if(dis - PLAYER_SIZE < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}