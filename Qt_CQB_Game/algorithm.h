//各种算法
#pragma once
#include <math.h>
#include "map.h"
#include "Player.h"
bool algo_CollisionDetection(double pos_x, double pos_y, wall * wall);//碰撞检测算法(玩家-墙体)
//static bool algo_CollisionDetection(Player * player, Player * player2);//碰撞检测算法(玩家-玩家)
bool algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y);//判断线段相交
bool algo_LookThrough(double A_x, double A_y, double B_x, double B_y, GameMap * map);//判断线是否被地图内固定元素遮挡
double algo_getLineAngle(QPointF startPoint, QPointF endPoint);//计算角色面朝方向角度