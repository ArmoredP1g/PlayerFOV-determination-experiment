#include "map.h"


GameMap::GameMap()
{

	//��������ǽ
	this->walls.push_back(wall{ QPointF(32,32),QPointF(992,32) });
	this->walls.push_back(wall{ QPointF(32,32),QPointF(32,544) });
	this->walls.push_back(wall{ QPointF(992,32),QPointF(992,544) });
	this->walls.push_back(wall{ QPointF(32,544),QPointF(900,544) });
}

GameMap::~GameMap()
{
}