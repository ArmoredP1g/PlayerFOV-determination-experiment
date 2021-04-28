#include "map.h"


GameMap::GameMap()
{

	//建筑物外墙
	this->walls.push_back(wall{ QPointF(32,32),QPointF(992,32) });
	this->walls.push_back(wall{ QPointF(32,32),QPointF(32,544) });
	this->walls.push_back(wall{ QPointF(992,32),QPointF(992,544) });
	this->walls.push_back(wall{ QPointF(32,544),QPointF(850,544) });

	//入口左手边墙
	this->walls.push_back(wall{ QPointF(850,544),QPointF(850,410) });
	//1号房间外墙
	this->walls.push_back(wall{ QPointF(850,330),QPointF(850,250) });
	this->walls.push_back(wall{ QPointF(550,250),QPointF(850,250) });
	this->walls.push_back(wall{ QPointF(550,250),QPointF(550,480) });
	//二号房间外墙
	this->walls.push_back(wall{ QPointF(550,180),QPointF(992,180) });
	//
	//
	//
	//
}

GameMap::~GameMap()
{
}