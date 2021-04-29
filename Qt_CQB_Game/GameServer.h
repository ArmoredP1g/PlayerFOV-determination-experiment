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

	unsigned int refreshRate_HZ = 60;//������ˢ����
	unsigned int pace = 140;//���ﲽ��
	QTimer *timer;
	GameMap * map;
	std::vector<Player *> PlayerList;//��������б�
	Player playerVisualMap[12][12];//��Ҽ��Ƿ�����ڶԷ���Ұ�ڵ�ͼ���������12��
	bool ObjectVisualMap[12][50];//�����Ƿ�����������Ұ�� ��������50��
	int newestPlayerId = -1;
	void addPlayer(Player * player);//������
	void addDummyEnemyPlayers();//*������*��Ӽ�Ŀ��
	void getPlayerAction();//��ȡ�����Ϊ
	void visualCalculate();//��ȡ��Ұ���������
	void loadMap(GameMap * map);
protected:
	void run();

};