#pragma once
#include <vector>
#include <qpoint.h>

typedef struct wall
{
	//就是个线段 两个端点坐标
	QPointF startPoint;
	QPointF endPoint;
}wall;

typedef struct box
{
	//矩形不可穿透物体
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

