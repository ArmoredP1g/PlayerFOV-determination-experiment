#pragma once
#include <vector>
#include <qpoint.h>

typedef struct wall
{
	//���Ǹ��߶� �����˵�����
	QPointF startPoint;
	QPointF endPoint;
}wall;

typedef struct box
{
	//���β��ɴ�͸����
	int lenth;
	int width;
	int position_x;
	int position_y;
	double rotation;
}box;

class GameMap
{
public:
	GameMap();
	~GameMap();
	std::vector<wall>walls;
	std::vector<box>boxes;
private:

};

