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
	unsigned int pace = 160;//���ﲽ��
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
	bool algo_CollisionDetection(double pos_x ,double pos_y,wall * wall);//��ײ����㷨(���-ǽ��)
	bool algo_CollisionDetection(Player * player, Player * player2);//��ײ����㷨(���-���)
	bool algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y);//�ж��߶��ཻ
	bool algo_LookThrough(double A_x, double A_y, double B_x, double B_y);//�ж����Ƿ񱻵�ͼ�ڹ̶�Ԫ���ڵ�
protected:
	void run();

};