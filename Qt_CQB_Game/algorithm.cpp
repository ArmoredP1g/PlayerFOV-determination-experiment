#include "algorithm.h"
#include "GameServer.h"
#include <iostream>
using namespace std;
//点与墙体的碰撞检测(两点式的点到直线距离公式推导,再判断端点边界)
bool algo_CollisionDetection(double pos_x, double pos_y, wall * wall)
{
	//情况一、点在线端点+人物半径 形成的矩形范围外，一定不会发生碰撞
	double x_max, x_min, y_max, y_min;
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
	//情况二、线段完全垂直，避免出现分母为0的情况，需要单独判断
	if (wall->startPoint.x() == wall->endPoint.x())
	{
		return true;//肯定碰撞了
	}
	//以上情况都不满足 正常求点到直线距离即可
	double dis = fabs(((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()))*pos_x - pos_y + wall->startPoint.y() - ((wall->endPoint.y() - wall->startPoint.y())*wall->startPoint.x()) / (wall->endPoint.x() - wall->startPoint.x()))
		/
		sqrt(pow((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()), 2) + 1);
	//cout << "人物与墙体距离:	" << dis << endl;
	if (dis - PLAYER_SIZE < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//用向量法判断线段相交，但并没考虑不会出现的几种特殊情况
//https://www.cnblogs.com/tuyang1129/p/9390376.html
bool algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y)
{
	//向量相乘 x1*y2 - x2*y1
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
//判断玩家是否能看到目标
bool algo_LookThrough(double target_x, double target_y, GameMap * map, Player * player)
{
	//先判断是否在视角内
	if (!algo_InFOV(player, QPointF(target_x, target_y)))
	{
		return false;
	}
	//再判断和墙体碰撞
	for (int wall_num = 0; wall_num < map->walls.size(); wall_num++)
	{
		if (algo_LineIntersect(player->pos_x, player->pos_y, target_x, target_y, map->walls[wall_num].startPoint.x(),
			map->walls[wall_num].startPoint.y(),
			map->walls[wall_num].endPoint.x(),
			map->walls[wall_num].endPoint.y()))

		{
			return false;
		}
	}
	return true;
}

//目标是否在玩家视野角内
bool algo_InFOV(Player * player, QPointF target)
{
	double upperLimit;
	double lowerLimit;
	double targetAngle = algo_getLineAngle(QPointF(player->pos_x, player->pos_y), target);
	//处理特殊区间
	if (player->facingAngle > 2 * M_PI - PLAYER_FOV)
	{
		upperLimit = player->facingAngle - 2 * M_PI + PLAYER_FOV;
		lowerLimit = player->facingAngle - 2 * M_PI - PLAYER_FOV;
	}
	else
	{
		upperLimit = player->facingAngle + PLAYER_FOV;
		lowerLimit = player->facingAngle - PLAYER_FOV;
	}
	//cout << "lowerLimit: " << lowerLimit << "	upperLimit: " << upperLimit << "	targetAngle: " << endl;

	if (lowerLimit < 0)
	{
		if (targetAngle > lowerLimit + 2 * M_PI)
		{
			targetAngle -= 2 * M_PI;
		}
	}

	if (targetAngle >= lowerLimit && targetAngle <= upperLimit)
	{
		//cout << "lowerLimit: " << lowerLimit << "	upperLimit: " << upperLimit << "	targetAngle: " << targetAngle << " 在" << endl;
		return true;
	}
	else
	{
		//cout<<"lowerLimit: "<< lowerLimit << "	upperLimit: " << upperLimit << "	targetAngle: " << targetAngle <<" 不在"<< endl;
		return false;
	}
}

//计算角色面朝方向角度 正上为0,顺时针算(qt这坐标y是反的)
double algo_getLineAngle(QPointF startPoint, QPointF endPoint)
{
	if (endPoint.x() - startPoint.x() > 0)
	{
		//如果终点在起点的右上
		if (endPoint.y() - startPoint.y() < 0)
		{
			return atan((endPoint.x()-startPoint.x())/(startPoint.y()-endPoint.y()));
		}
		//如果终点在起点的右下
		if (endPoint.y() - startPoint.y() > 0)
		{
			return 0.5*M_PI + atan((endPoint.y()-startPoint.y())/(endPoint.x() - startPoint.x()));
		}
	}
	if (endPoint.x() - startPoint.x() < 0)
	{
		//如果终点在起点的左上
		if (endPoint.y() - startPoint.y() < 0)
		{
			return 1.5*M_PI + atan((startPoint.y()-endPoint.y())/(startPoint.x()-endPoint.x()));
		}
		//如果终点在起点的左下
		if (endPoint.y() - startPoint.y() > 0)
		{
			return M_PI + atan((startPoint.x()-endPoint.x())/(endPoint.y()-startPoint.y()));
		}
	}

	if (endPoint.x() == startPoint.x())
	{
		//如果终点在起点的正下
		if (startPoint.y() < endPoint.y())
		{
			return M_PI;
		}
		//如果终点在起点的正上
		if (startPoint.y() > endPoint.y())
		{
			return 0;
		}
	}

	if (endPoint.y() == startPoint.y())
	{
		//如果终点在起点的正左
		if (endPoint.x() < startPoint.x())
		{
			return 1.5 * M_PI;
		}
		//如果终点在起点的正右
		if (endPoint.x() > startPoint.x())
		{
			return 0.5 * M_PI;
		}
	}
	//原点返回0
	return 0;
}

//绕端点旋转视线边界线段,正顺时针负逆时针,返回终点新坐标,(依赖algo_getLineAngle函数)
QPointF algo_rotateLineByAngle(QPointF startPoint, QPointF endPoint,double rotate_angle)
{
	QPointF result;
	double angle_start = algo_getLineAngle(startPoint,endPoint) ;
	double lenth = sqrt(pow(startPoint.x()-endPoint.x(), 2)+ pow(startPoint.y() - endPoint.y(), 2));//线段长度
	double angle = angle_start + rotate_angle;//直线最终的角度

	//处理区间外的情况
	if (angle >= 2 * M_PI)
	{
		angle -= 2 * M_PI;
	}
	if (angle < 0)
	{
		angle += 2 * M_PI;
	}

	//右上象限
	if (angle > 0 && angle < 0.5*M_PI)
	{
		result.setX(startPoint.x() + sin(angle)*lenth);
		result.setY(startPoint.y() - cos(angle)*lenth);
		return result;
	}
	//右下象限
	if (angle > 0.5*M_PI && angle < M_PI)
	{
		result.setX(startPoint.x() + cos(angle-0.5*M_PI)*lenth);
		result.setY(startPoint.y() + sin(angle - 0.5*M_PI)*lenth);
		return result;
	}
	//左下象限
	if (angle > M_PI && angle < 1.5*M_PI)
	{
		result.setX(startPoint.x() - sin(angle - M_PI)*lenth);
		result.setY(startPoint.y() + cos(angle - M_PI)*lenth);
		return result;
	}
	//左上象限
	if (angle > 1.5*M_PI && angle < 2 * M_PI)
	{
		result.setX(startPoint.x() - cos(angle - 1.5*M_PI)*lenth);
		result.setY(startPoint.y() - sin(angle - 1.5*M_PI)*lenth);
		return result;
	}
	//正上
	if (angle == 0)
	{
		result.setX(startPoint.x());
		result.setY(startPoint.y() - lenth);
		return result;
	}
	//正右
	if (angle == 0.5*M_PI)
	{
		result.setX(startPoint.x() + lenth);
		result.setY(startPoint.y());
		return result;
	}
	//正下
	if (angle == M_PI)
	{
		result.setX(startPoint.x());
		result.setY(startPoint.y() + lenth);
		return result;
	}
	//正左
	if (angle == 1.5*M_PI)
	{
		result.setX(startPoint.x() - lenth);
		result.setY(startPoint.y());
		return result;
	}

	//这些都不满足 只能是原点
	return startPoint;
}

//固定长度的射线
QPointF algo_rotateLineByAngle(QPointF startPoint, QPointF endPoint, double rotate_angle ,double fixLenth)
{
	QPointF result;
	double angle_start = algo_getLineAngle(startPoint, endPoint);
	double lenth = fixLenth;//线段长度
	double angle = angle_start + rotate_angle;//直线最终的角度

	//处理区间外的情况
	if (angle >= 2 * M_PI)
	{
		angle -= 2 * M_PI;
	}
	if (angle < 0)
	{
		angle += 2 * M_PI;
	}

	//右上象限
	if (angle > 0 && angle < 0.5*M_PI)
	{
		result.setX(startPoint.x() + sin(angle)*lenth);
		result.setY(startPoint.y() - cos(angle)*lenth);
		return result;
	}
	//右下象限
	if (angle > 0.5*M_PI && angle < M_PI)
	{
		result.setX(startPoint.x() + cos(angle - 0.5*M_PI)*lenth);
		result.setY(startPoint.y() + sin(angle - 0.5*M_PI)*lenth);
		return result;
	}
	//左下象限
	if (angle > M_PI && angle < 1.5*M_PI)
	{
		result.setX(startPoint.x() - sin(angle - M_PI)*lenth);
		result.setY(startPoint.y() + cos(angle - M_PI)*lenth);
		return result;
	}
	//左上象限
	if (angle > 1.5*M_PI && angle < 2 * M_PI)
	{
		result.setX(startPoint.x() - cos(angle - 1.5*M_PI)*lenth);
		result.setY(startPoint.y() - sin(angle - 1.5*M_PI)*lenth);
		return result;
	}
	//正上
	if (angle == 0)
	{
		result.setX(startPoint.x());
		result.setY(startPoint.y() - lenth);
		return result;
	}
	//正右
	if (angle == 0.5*M_PI)
	{
		result.setX(startPoint.x() + lenth);
		result.setY(startPoint.y());
		return result;
	}
	//正下
	if (angle == M_PI)
	{
		result.setX(startPoint.x());
		result.setY(startPoint.y() + lenth);
		return result;
	}
	//正左
	if (angle == 1.5*M_PI)
	{
		result.setX(startPoint.x() - lenth);
		result.setY(startPoint.y());
		return result;
	}

	//这些都不满足 只能是原点
	return startPoint;
}