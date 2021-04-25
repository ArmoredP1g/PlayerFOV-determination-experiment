#include "GameScenes.h"
#include "GameWidget.h"
#include "Result.h"

//初始化所有游戏场景
GameScenes::GameScenes(QWidget *parent,GameMap * map,GameServer * server)
	: QWidget(parent)
{
	scenes[0] = new GameWidget(this,map,&Player_yourself);
	scenes[1] = new ResultWidget(this);
	server->addPlayer(&Player_yourself);
}

QWidget ** GameScenes::getScenes()
{
	//返回首地址
	return &scenes[0];
}

GameScenes::~GameScenes()
{
	delete scenes[0];
	delete scenes[1];
}