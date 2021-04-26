#include"GameServer.h"
#include<iostream>
using namespace std;

GameServer::GameServer(QObject *parent)
{
	//���÷�����ˢ��Ƶ��
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout,this, &GameServer::run);
	timer->start(1000/refreshRate_HZ);
}

GameServer::~GameServer()
{

}

void GameServer::run()
{
	//��ȡ�����Ϊ
	//calculate game events
	getPlayerAction();
}

void GameServer::loadMap(GameMap * map)
{
	this->map = map;
}

 void GameServer::addPlayer(Player * player)
{
	//����ҷ���һ��id
	player->player_id = ++newestPlayerId;
	player->pos_x = 0;
	player->pos_y = 0;
	PlayerList.push_back(player);
}

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
	}
}

//����ǽ�����ײ���(����ʽ�ĵ㵽ֱ�߾��빫ʽ)
bool GameServer::algo_CollisionDetection(double pos_x, double pos_y, wall * wall)
{
	//���һ�������߶˵�+����뾶 �γɵľ��η�Χ�⣬һ�����ᷢ����ײ
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
	//��������߶���ȫ��ֱ��������ַ�ĸΪ0���������Ҫ�����ж�
	if (wall->startPoint.x() == wall->endPoint.x())
	{
		return true;//�϶���ײ��
	}
	//��������������� ������㵽ֱ�߾��뼴��
	double dis = fabs(((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()))*pos_x - pos_y + wall->startPoint.y() - ((wall->endPoint.y() - wall->startPoint.y())*wall->startPoint.x()) / (wall->endPoint.x() - wall->startPoint.x()))
		/
		sqrt(pow((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()), 2) + 1);
	//cout << "������ǽ�����:	" << dis << endl;
	if(dis - PLAYER_SIZE < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}