//�����㷨
#pragma once
#include <math.h>
#include "map.h"
#include "Player.h"
bool algo_CollisionDetection(double pos_x, double pos_y, wall * wall);//��ײ����㷨(���-ǽ��)
//static bool algo_CollisionDetection(Player * player, Player * player2);//��ײ����㷨(���-���)
bool algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y);//�ж��߶��ཻ
bool algo_LookThrough(double A_x, double A_y, double B_x, double B_y, GameMap * map);//�ж����Ƿ񱻵�ͼ�ڹ̶�Ԫ���ڵ�
double algo_getLineAngle(QPointF startPoint, QPointF endPoint);//�����ɫ�泯����Ƕ�