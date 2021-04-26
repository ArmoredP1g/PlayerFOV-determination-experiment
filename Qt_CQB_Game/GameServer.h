#pragma once
#include <qthread.h>
#include "Player.h"
#include <vector>
#include <qtimer.h>
#include "map.h"
#include <qmath.h>

#define PLAYER_SIZE 10
//��Ϸ��̨�ж�
class GameServer : public QThread
{
	Q_OBJECT
public:
	GameServer(QObject *parent = NULL);
	~GameServer();

	unsigned int refreshRate_HZ = 160;//������ˢ����
	unsigned int pace = 160;//���ﲽ��
	QTimer *timer;
	GameMap * map;
	std::vector<Player *> PlayerList;
	int newestPlayerId = -1;
	void addPlayer(Player * player);//������
	void getPlayerAction();//��ȡ�����Ϊ
	void loadMap(GameMap * map);
	bool algo_CollisionDetection(double pos_x ,double pos_y,wall * wall);//��ײ����㷨(���-ǽ��)
	bool algo_CollisionDetection(Player * player, Player * player2);//��ײ����㷨(���-���)
protected:
	void run();

};