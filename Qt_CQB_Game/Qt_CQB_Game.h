#pragma once

#include <QtWidgets/QWidget>
#include "ui_Qt_CQB_Game.h"
#include "GameScenes.h"
#include "map.h"
#include "GameServer.h"
class Qt_CQB_Game : public QWidget
{
    Q_OBJECT

public:
    Qt_CQB_Game(QWidget *parent = Q_NULLPTR);
	
private:
	
    Ui::Qt_CQB_GameClass ui;
	GameScenes * gameScenes;
	GameMap * map;
	GameServer * server;
public slots:
	void getGameScene();
	void getResultScene();
};
