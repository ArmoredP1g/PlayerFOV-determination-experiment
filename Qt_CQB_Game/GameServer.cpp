#include"GameServer.h"
#include<iostream>
using namespace std;

GameServer::GameServer(QObject *parent)
{
	//���÷�����ˢ��Ƶ��
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout,this, &GameServer::run);
	connect(timer, &QTimer::timeout, this, &GameServer::visualCalculate);
	timer->start(1000/refreshRate_HZ);
}

GameServer::~GameServer()
{

}

//ֻ������Ҳ�����Ϊ
void GameServer::run()
{
	//��ȡ�����Ϊ
	//calculate game events
	getPlayerAction();
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
				//�ŵ��жϷ� ���ж�ǽ����
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x,
					PlayerList[j]->pos_y))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x,
					PlayerList[j]->pos_y - PLAYER_SIZE))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x + sqrt(PLAYER_SIZE),
					PlayerList[j]->pos_y - sqrt(PLAYER_SIZE)))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x + PLAYER_SIZE,
					PlayerList[j]->pos_y))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x + sqrt(PLAYER_SIZE),
					PlayerList[j]->pos_y + sqrt(PLAYER_SIZE)))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y + PLAYER_SIZE,
					PlayerList[j]->pos_x,
					PlayerList[j]->pos_y))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x - sqrt(PLAYER_SIZE),
					PlayerList[j]->pos_y + sqrt(PLAYER_SIZE)))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//��
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x - PLAYER_SIZE,
					PlayerList[j]->pos_y))
				{
					playerVisualMap[i][j].visibility = true;
					playerVisualMap[i][j].pos_x = PlayerList[j]->pos_x;
					playerVisualMap[i][j].pos_y = PlayerList[j]->pos_y;
					continue;
				}
				//����
				if (algo_LookThrough(PlayerList[i]->pos_x,
					PlayerList[i]->pos_y,
					PlayerList[j]->pos_x - sqrt(PLAYER_SIZE),
					PlayerList[j]->pos_y - sqrt(PLAYER_SIZE)))
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

//����ǽ�����ײ���(����ʽ�ĵ㵽ֱ�߾��빫ʽ�Ƶ�,���ж϶˵�߽�)
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

//���������ж��߶��ཻ������û���ǲ�����ֵļ����������
//https://www.cnblogs.com/tuyang1129/p/9390376.html
bool GameServer::algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y)
{
	//������� x1*y2 - x2*y1
	bool condition1 = false;
	bool condition2 = false;
	
	double vecAC_x, vecAC_y;
	double vecAD_x, vecAD_y;
	double vecAB_x, vecAB_y;
	
	double vecCA_x, vecCA_y;
	double vecCB_x, vecCB_y;
	double vecCD_x, vecCD_y;

	double ACxAB, ADxAB;
	double CAxCD, CBxCD;

	vecCD_x = D_x - C_x; vecCD_y = D_y - C_y;
	vecAC_x = C_x - A_x; vecAC_y = C_y - A_y;
	vecAD_x = D_x - A_x; vecAD_y = D_y - A_y;

	vecAB_x = B_x - A_x; vecAB_y = B_y - A_y;
	vecCA_x = A_x - C_x; vecCA_y = A_y - C_y;
	vecCB_x = B_x - C_x; vecCB_y = B_y - C_y;

	ACxAB = vecAC_x * vecAB_y - vecAB_x * vecAC_y;
	ADxAB = vecAD_x * vecAB_y - vecAB_x * vecAD_y;

	CAxCD = vecCA_x * vecCD_y - vecCD_x * vecCA_y;
	CBxCD = vecCB_x * vecCD_y - vecCD_x * vecCB_y;

	if ((ACxAB * ADxAB <= 0) && (CAxCD * CBxCD <= 0))
	{
		return true;
	}
	else 
	{
		return false;
	}

}
//�ж����Ƿ񱻵�ͼ�ڹ̶�Ԫ���ڵ�
bool GameServer::algo_LookThrough(double A_x, double A_y, double B_x, double B_y)
{
	for (int wall_num = 0; wall_num < map->walls.size(); wall_num++)
	{
		if (algo_LineIntersect(A_x, A_y, B_x, B_y,map->walls[wall_num].startPoint.x(),
			map->walls[wall_num].startPoint.y(),
			map->walls[wall_num].endPoint.x(),
			map->walls[wall_num].endPoint.y()))

		{
			return false;
		}
	}
	return true;
}