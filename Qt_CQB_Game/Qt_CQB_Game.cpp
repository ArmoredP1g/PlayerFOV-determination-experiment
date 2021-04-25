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
	//����Ϸ����װ�ص�stackedwidget��
	ui.widget_mainGameWidget->addWidget(*(gameScenes->getScenes()));
	ui.widget_mainGameWidget->addWidget(*(gameScenes->getScenes() + 1));

	connect(this->ui.pushButton_OnGame,&QPushButton::clicked,this,&Qt_CQB_Game::getGameScene);
	connect(this->ui.pushButton_Result, &QPushButton::clicked, this, &Qt_CQB_Game::getResultScene);
}


//�ۺ�������ȡ��Ϸ����
void Qt_CQB_Game::getGameScene()
{
	ui.widget_mainGameWidget->setCurrentIndex(0);
}

//�ۺ�������ȡ�������
void Qt_CQB_Game::getResultScene()
{
	ui.widget_mainGameWidget->setCurrentIndex(1);
}
