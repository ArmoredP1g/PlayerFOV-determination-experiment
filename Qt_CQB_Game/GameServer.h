#pragma once
#include <qthread.h>
#include "Player.h"
#include <vector>
#include <qtimer.h>
#include "map.h"
//��Ϸ��̨�ж�
class GameServer : public QThread
{
	Q_OBJECT
public:
	GameServer(QObject *parent = NULL);
	~GameServer();

	unsigned int refreshRate_HZ = 30;//������ˢ����
	unsigned int pace = 60;//���ﲽ��
	QTimer *timer;
	std::vector<Player *> PlayerList;
	int newestPlayerId = -1;
	void addPlayer(Player * player);//������
	void getPlayerAction();//��ȡ�����Ϊ
	bool algo_CollisionDetection(Player * player,wall * wall);//��ײ����㷨(���-ǽ��)
	bool algo_CollisionDetection(Player * player, Player * player2);//��ײ����㷨(���-���)
protected:
	void run();

};