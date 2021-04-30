//各种算法
#pragma once
#include <math.h>
#include "map.h"
#include "Player.h"
bool algo_CollisionDetection(double pos_x, double pos_y, wall * wall);//碰撞检测算法(玩家-墙体)
//static bool algo_CollisionDetection(Player * player, Player * player2);//碰撞检测算法(玩家-玩家)
bool algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y);//判断线段相交
bool algo_LookThrough(double target_x, double target_y, GameMap * map, Player * player);//判断玩家是否能看到目标
bool algo_InFOV(Player * player, QPointF target);//目标是否在玩家视野角内
double algo_getLineAngle(QPointF startPoint, QPointF endPoint);//计算角色面朝方向角度
QPointF algo_rotateLineByAngle(QPointF startPoint, QPointF endPoint, double rotate_angle);//绕端点旋转视线边界线段,正顺时针负逆时针,返回终点新坐标,(依赖algo_getLineAngle函数)
QPointF algo_rotateLineByAngle(QPointF startPoint, QPointF endPoint, double rotate_angle,double fixLenth);//重载 长度固定的射线