#include "algorithm.h"
#include "GameServer.h"
//����ǽ�����ײ���(����ʽ�ĵ㵽ֱ�߾��빫ʽ�Ƶ�,���ж϶˵�߽�)
bool algo_CollisionDetection(double pos_x, double pos_y, wall * wall)
{
	//���һ�������߶˵�+����뾶 �γɵľ��η�Χ�⣬һ�����ᷢ����ײ
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
	//��������߶���ȫ��ֱ��������ַ�ĸΪ0���������Ҫ�����ж�
	if (wall->startPoint.x() == wall->endPoint.x())
	{
		return true;//�϶���ײ��
	}
	//��������������� ������㵽ֱ�߾��뼴��
	double dis = fabs(((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()))*pos_x - pos_y + wall->startPoint.y() - ((wall->endPoint.y() - wall->startPoint.y())*wall->startPoint.x()) / (wall->endPoint.x() - wall->startPoint.x()))
		/
		sqrt(pow((wall->endPoint.y() - wall->startPoint.y()) / (wall->endPoint.x() - wall->startPoint.x()), 2) + 1);
	//cout << "������ǽ�����:	" << dis << endl;
	if (dis - PLAYER_SIZE < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//���������ж��߶��ཻ������û���ǲ�����ֵļ����������
//https://www.cnblogs.com/tuyang1129/p/9390376.html
bool algo_LineIntersect(double A_x, double A_y, double B_x, double B_y, double C_x, double C_y, double D_x, double D_y)
{
	//������� x1*y2 - x2*y1
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
//�ж����Ƿ񱻵�ͼ�ڹ̶�Ԫ���ڵ�
bool algo_LookThrough(double A_x, double A_y, double B_x, double B_y, GameMap * map)
{
	for (int wall_num = 0; wall_num < map->walls.size(); wall_num++)
	{
		if (algo_LineIntersect(A_x, A_y, B_x, B_y, map->walls[wall_num].startPoint.x(),
			map->walls[wall_num].startPoint.y(),
			map->walls[wall_num].endPoint.x(),
			map->walls[wall_num].endPoint.y()))

		{
			return false;
		}
	}
	return true;
}

//�����ɫ�泯����Ƕ�(qt������y�Ƿ���)
double algo_getLineAngle(QPointF startPoint, QPointF endPoint)
{
	if (endPoint.x() - startPoint.x() > 0)
	{
		//����յ�����������
		if (endPoint.y() - startPoint.y() < 0)
		{
			return atan((endPoint.x()-startPoint.x())/(startPoint.y()-endPoint.y()));
		}
		//����յ�����������
		if (endPoint.y() - startPoint.y() > 0)
		{
			return 0.5*M_PI + atan((endPoint.y()-startPoint.y())/(endPoint.x() - startPoint.x()));
		}
	}
	if (endPoint.x() - startPoint.x() < 0)
	{
		//����յ�����������
		if (endPoint.y() - startPoint.y() < 0)
		{
			return 1.5*M_PI + atan((startPoint.y()-endPoint.y())/(startPoint.x()-endPoint.x()));
		}
		//����յ�����������
		if (endPoint.y() - startPoint.y() > 0)
		{
			return M_PI + atan((startPoint.x()-endPoint.x())/(endPoint.y()-startPoint.y()));
		}
	}

	if (endPoint.x() == startPoint.x())
	{
		//����յ�����������
		if (startPoint.y() < endPoint.y())
		{
			return M_PI;
		}
		//����յ�����������
		if (startPoint.y() > endPoint.y())
		{
			return 0;
		}
	}

	if (endPoint.y() == startPoint.y())
	{
		//����յ�����������
		if (endPoint.x() < startPoint.x())
		{
			return 1.5 * M_PI;
		}
		//����յ�����������
		if (endPoint.x() > startPoint.x())
		{
			return 0.5 * M_PI;
		}
	}
	//ԭ�㷵��0
	return 0;
}