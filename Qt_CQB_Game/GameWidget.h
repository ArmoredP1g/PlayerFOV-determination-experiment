#pragma once
#include <QtWidgets/QWidget>
#include "ui_GameWidget.h"
#include "GameServer.h"
#include "map.h"
#include"Player.h"
#include<QKeyEvent>
#include<qtimer.h>
class GameWidget : public QWidget
{
	Q_OBJECT

public:
	GameWidget(QWidget *parent, GameMap * map ,Player * player_self,GameServer * gameServer);
	int count;

private:
	Ui::gameWidget ui;
	GameMap * map;
	Player * Player_yourself;
	QTimer *timer;
	GameServer * server;
protected:
	void paintEvent(QPaintEvent *);
	void keyPressEvent(QKeyEvent * e);
	void keyReleaseEvent(QKeyEvent * e);
	void mouseMoveEvent(QMouseEvent * e);
	void refreshUI();
	void DEBUG_DrawVisualLines();//œ‘ æ ”“∞œﬂ
};