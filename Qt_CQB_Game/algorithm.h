//�����㷨
#pragma once
#include <math.h>
#include "map.h"
#include "Player.h"
bool algo_CollisionDetection(double pos_x, double pos_y, wall * wall);//��ײ����㷨(���-ǽ��)
//static bool algo_CollisionDetection(Player * player, Player * player2);//��ײ����㷨(���-���)
bool algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y);//�ж��߶��ཻ
bool algo_LookThrough(double target_x, double target_y, GameMap * map, Player * player);//�ж�����Ƿ��ܿ���Ŀ��
bool algo_InFOV(Player * player, QPointF target);//Ŀ���Ƿ��������Ұ����
double algo_getLineAngle(QPointF startPoint, QPointF endPoint);//�����ɫ�泯����Ƕ�
QPointF algo_rotateLineByAngle(QPointF startPoint, QPointF endPoint, double rotate_angle);//�ƶ˵���ת���߽߱��߶�,��˳ʱ�븺��ʱ��,�����յ�������,(����algo_getLineAngle����)
QPointF algo_rotateLineByAngle(QPointF startPoint, QPointF endPoint, double rotate_angle,double fixLenth);//���� ���ȹ̶�������