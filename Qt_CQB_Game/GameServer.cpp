#include"GameServer.h"
#include<iostream>

using namespace std;

GameServer::GameServer(QObject *parent)
{
	//���÷�����ˢ��Ƶ��
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout,this, &GameServer::getPlayerAction);//��ȡ�����Ϊ
	connect(timer, &QTimer::timeout, this, &GameServer::visualCalculate);
	timer->start(1000/refreshRate_HZ);
}

GameServer::~GameServer()
{

}


void GameServer::run()
{

}

//������Ұ
void GameServer::visualCalculate()
{
	//��ҿɼ���ͼ
	for (int i=0; i < PlayerList.size(); i++)
	{
		for (int j = 0; j < PlayerList.size(); j++)
		{
			if (i != j)//�Լ������Լ��ж�
			{
				//�ŵ��жϷ�
				if (algo_LookThrough(PlayerList[j]->pos_x,PlayerList[j]->pos_y,map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[j]->pos_x, PlayerList[j]->pos_y - PLAYER_SIZE, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[j]->pos_x + PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y - PLAYER_SIZE / sqrt(2), map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[j]->pos_x + PLAYER_SIZE, PlayerList[j]->pos_y, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[j]->pos_x + PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y + PLAYER_SIZE / sqrt(2), map, PlayerList[i]))			
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[j]->pos_x, PlayerList[j]->pos_y + PLAYER_SIZE, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[j]->pos_x - PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y + PLAYER_SIZE / sqrt(2), map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[j]->pos_x - PLAYER_SIZE, PlayerList[j]->pos_y, map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[j]->pos_x - PLAYER_SIZE / sqrt(2), PlayerList[j]->pos_y - PLAYER_SIZE / sqrt(2), map, PlayerList[i]))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//�ŵ��жϷ� ���ж�������(Ŀǰû����)
				
				//��û��
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
	//����ҷ���һ��id
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
                                                                                       
 //ֻ������Ҳ�����Ϊ
void GameServer::getPlayerAction()
{
	for (int players = 0; players < PlayerList.size(); players++)
	{
		//�ж��ƶ�;
		//ǰ
		if (PlayerList[players]->behavior_move_ahead)
		{
			//������ײ���
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


		//��
		if (PlayerList[players]->behavior_move_back)
		{
			//������ײ���
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
			//������ײ���
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
			//������ײ���
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

		//�ж���ҳ���
		PlayerList[players]->facingAngle = algo_getLineAngle(QPointF(PlayerList[players]->pos_x, PlayerList[players]->pos_y),
															 QPointF(PlayerList[players]->facingVec_x, PlayerList[players]->facingVec_y));
	}
}
