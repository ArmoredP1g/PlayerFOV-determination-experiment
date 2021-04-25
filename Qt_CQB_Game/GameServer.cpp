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


 void GameServer::addPlayer(Player * player)
{
	//����ҷ���һ��id
	player->player_id = ++newestPlayerId;
	player->pos_x = 20;
	player->pos_y = 20;
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
			//û��ײ���
			PlayerList[players]->pos_y -= (pace / refreshRate_HZ);
		}
		//��
		if (PlayerList[players]->behavior_move_back)
		{
			//û��ײ���
			PlayerList[players]->pos_y += (pace / refreshRate_HZ);
		}
		//left
		if (PlayerList[players]->behavior_move_left)
		{
			//û��ײ���
			PlayerList[players]->pos_x -= (pace / refreshRate_HZ);
		}
		//right
		if (PlayerList[players]->behavior_move_right)
		{
			//û��ײ���
			PlayerList[players]->pos_x += (pace / refreshRate_HZ);
		}
	}
}