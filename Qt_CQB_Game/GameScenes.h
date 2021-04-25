#pragma once
#include <QtWidgets/QWidget>
#include "ui_GameWidget.h"
#include "ui_Result.h"
#include "GameServer.h"
#include "map.h"
class GameScenes : public QWidget
{
	Q_OBJECT

public:
	GameScenes(QWidget *parent, GameMap * map, GameServer * server);
	~GameScenes();
	QWidget ** getScenes();
	QWidget * scenes[2];
	Player Player_yourself;
private:
	
};


