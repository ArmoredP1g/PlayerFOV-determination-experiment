#include "Qt_CQB_Game.h"
#include <iostream>
using namespace std;
Qt_CQB_Game::Qt_CQB_Game(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	server = new GameServer;
	server->start();
	map = new GameMap;
	gameScenes = new GameScenes(this,map,server);
	//把游戏界面装载到stackedwidget中
	ui.widget_mainGameWidget->addWidget(*(gameScenes->getScenes()));
	ui.widget_mainGameWidget->addWidget(*(gameScenes->getScenes() + 1));

	connect(this->ui.pushButton_OnGame,&QPushButton::clicked,this,&Qt_CQB_Game::getGameScene);
	connect(this->ui.pushButton_Result, &QPushButton::clicked, this, &Qt_CQB_Game::getResultScene);
}


//槽函数：调取游戏界面
void Qt_CQB_Game::getGameScene()
{
	ui.widget_mainGameWidget->setCurrentIndex(0);
}

//槽函数：调取结算界面
void Qt_CQB_Game::getResultScene()
{
	ui.widget_mainGameWidget->setCurrentIndex(1);
}
