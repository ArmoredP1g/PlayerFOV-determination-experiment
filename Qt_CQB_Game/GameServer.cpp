#include"GameServer.h"
#include<iostream>

using namespace std;

GameServer::GameServer(QObject *parent)
{
	//配置服务器刷新频率
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout,this, &GameServer::getPlayerAction);//获取玩家行为
	connect(timer, &QTimer::timeout, this, &GameServer::visualCalculate);
	timer->start(1000/refreshRate_HZ);
}

GameServer::~GameServer()
{

}


void GameServer::run()
{

}

//处理视野
void GameServer::visualCalculate()
{
	//玩家可见性图
	for (int i=0; i < PlayerList.size(); i++)
	{
		for (int j = 0; j < PlayerList.size(); j++)
		{
			if (i != j)//自己不跟自己判断
			{
				//九点判断法
				if (algo_LookThrough(PlayerList[j]->pos_x,PlayerList[j]->pos_y,map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//上
				if (algo_LookThrough(PlayerList[j]->pos_x, PlayerList[j]->pos_y - PLAYER_SIZE, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//右上
				if (algo_LookThrough(PlayerList[j]->pos_x + PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y - PLAYER_SIZE / sqrt(2), map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//右
				if (algo_LookThrough(PlayerList[j]->pos_x + PLAYER_SIZE, PlayerList[j]->pos_y, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//右下
				if (algo_LookThrough(PlayerList[j]->pos_x + PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y + PLAYER_SIZE / sqrt(2), map, PlayerList[i]))			
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//下
				if (algo_LookThrough(PlayerList[j]->pos_x, PlayerList[j]->pos_y + PLAYER_SIZE, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//左下
				if (algo_LookThrough(PlayerList[j]->pos_x - PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y + PLAYER_SIZE / sqrt(2), map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//左
				if (algo_LookThrough(PlayerList[j]->pos_x - PLAYER_SIZE, PlayerList[j]->pos_y, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//左上
				if (algo_LookThrough(PlayerList[j]->pos_x - PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y - PLAYER_SIZE / sqrt(2), map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//九点判断法 再判断物体组(目前没物体)
				
				//都没有
				playerVisualMap[i][j].visibility = false;
			}
		}
	}
}

void GameServer::loadMap(GameMap * map)
{
	this->map = map;
}

 void GameServer::addPlayer(Player * player)
{
	//给玩家分配一个id
	player->player_id = ++newestPlayerId;
	player->pos_x = 20;
	player->pos_y = 20;
	PlayerList.push_back(player);
}

 void GameServer::addDummyEnemyPlayers()
 {
	 Player * player1 = new Player;
	 player1->player_id = ++newestPlayerId;
	 player1->team = 2;
	 player1->pos_x = 64;
	 player1->pos_y = 64;
	 PlayerList.push_back(player1);

	 Player * player2 = new Player;
	 player2->player_id = ++newestPlayerId;
	 player2->team = 2;
	 player2->pos_x = 64;
	 player2->pos_y = 500;
	 PlayerList.push_back(player2);

	 Player * player3 = new Player;
	 player3->player_id = ++newestPlayerId;
	 player3->team = 2;
	 player3->pos_x = 300;
	 player3->pos_y = 500;
	 PlayerList.push_back(player3);

	 Player * player4 = new Player;
	 player4->player_id = ++newestPlayerId;
	 player4->team = 2;
	 player4->pos_x = 300;
	 player4->pos_y = 64;
	 PlayerList.push_back(player4);

	 Player * player5 = new Player;
	 player5->player_id = ++newestPlayerId;
	 player5->team = 2;
	 player5->pos_x = 250;
	 player5->pos_y = 250;
	 PlayerList.push_back(player5);
 }
                                                                                       
 //只处理玩家操作行为
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

		//判断玩家朝向
		PlayerList[players]->facingAngle = algo_getLineAngle(QPointF(PlayerList[players]->pos_x, PlayerList[players]->pos_y),
															 QPointF(PlayerList[players]->facingVec_x, PlayerList[players]->facingVec_y));
	}
}
