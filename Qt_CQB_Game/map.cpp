#include "map.h"


GameMap::GameMap()
{

	//��������ǽ
	this->walls.push_back(wall{ QPointF(32,32),QPointF(992,32) });
	this->walls.push_back(wall{ QPointF(32,32),QPointF(32,544) });
	this->walls.push_back(wall{ QPointF(992,32),QPointF(992,544) });
	this->walls.push_back(wall{ QPointF(32,544),QPointF(850,544) });

	//������ֱ�ǽ
	this->walls.push_back(wall{ QPointF(850,544),QPointF(850,410) });
	//1�ŷ�����ǽ
	this->walls.push_back(wall{ QPointF(850,330),QPointF(850,250) });
	this->walls.push_back(wall{ QPointF(550,250),QPointF(850,250) });
	this->walls.push_back(wall{ QPointF(550,250),QPointF(550,480) });
	//���ŷ�����ǽ
	this->walls.push_back(wall{ QPointF(550,180),QPointF(992,180) });
	//
	//
	//
	//
}

GameMap::~GameMap()
{
}