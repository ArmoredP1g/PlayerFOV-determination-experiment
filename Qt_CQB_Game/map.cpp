#include "map.h"


GameMap::GameMap()
{
	this->walls.push_back(wall{ QPointF(32,32),QPointF(992,32) });
	this->walls.push_back(wall{ QPointF(32,32),QPointF(32,544) });
	this->walls.push_back(wall{ QPointF(992,32),QPointF(992,544) });
	this->walls.push_back(wall{ QPointF(32,544),QPointF(942,544) });
}

GameMap::~GameMap()
{
}