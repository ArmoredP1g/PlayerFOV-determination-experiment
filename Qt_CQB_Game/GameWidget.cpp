#include "GameWidget.h"

#include <iostream>
#include <QPainter>
using namespace std;
GameWidget::GameWidget(QWidget *parent,GameMap * map, Player * player_self,GameServer * gameServer)
	: QWidget(parent)
{
	count = 0;
	this->grabKeyboard();
	
	//初始化前端界面
	Player_yourself = player_self;
	this->map = map;
	this->server = gameServer;
	//配置界面刷新为100hz
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameWidget::refreshUI);
	timer->start(1000 / 100);
	ui.setupUi(this);
}


//drawing event
void GameWidget::paintEvent(QPaintEvent *)
{
	//cout << "绘图事件被调用 " << ++count << " 次" << endl;
	//paintevent会覆盖掉stylesheet的样式，需要加上这几句，Qframe没这个问题
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	/********************************************************/
	QPainter painter(this);
	QPen pen; //画笔
	pen.setColor(QColor(255, 255, 255));
	pen.setWidth(3);
	painter.setPen(pen);

	//绘制地图
	for (int i = 0; i < map->walls.size(); i++)
	{
		painter.drawLine(map->walls[i].startPoint, map->walls[i].endPoint);
	}

	//绘制玩家
	pen.setColor(QColor(255, 255, 0));
	pen.setWidth(1);
	painter.setPen(pen);

	painter.drawEllipse(QRectF(Player_yourself->pos_x-10, Player_yourself->pos_y-10,20,20));

	//绘制视野内其他玩家
	pen.setColor(QColor(255, 40, 40));
	pen.setWidth(1);
	painter.setPen(pen);
	for (int i = 0; i < 12; i++)
	{
		if (server->playerVisualMap[Player_yourself->player_id][i].visibility)
		{
			painter.drawEllipse(QRectF(server->playerVisualMap[Player_yourself->player_id][i].pos_x - 10, 
				server->playerVisualMap[Player_yourself->player_id][i].pos_y - 10, 20, 20));
		}
	}
	//绘制交互物体
}
//key press events
void GameWidget::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_A)
	{
		Player_yourself->behavior_move_left = true;
	}
	if (e->key() == Qt::Key_D)
	{
		Player_yourself->behavior_move_right = true;
	}
	if (e->key() == Qt::Key_S)
	{
		Player_yourself->behavior_move_back = true;
	}
	if (e->key() == Qt::Key_W)
	{
		Player_yourself->behavior_move_ahead = true;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Player_yourself->behavior_move_speedUp = true;
	}
}
void GameWidget::keyReleaseEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_A)
	{
		Player_yourself->behavior_move_left = false;
	}
	if (e->key() == Qt::Key_D)
	{
		Player_yourself->behavior_move_right = false;
	}
	if (e->key() == Qt::Key_S)
	{
		Player_yourself->behavior_move_back = false;
	}
	if (e->key() == Qt::Key_W)
	{
		Player_yourself->behavior_move_ahead = false;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Player_yourself->behavior_move_speedUp = false;
	}
}

void GameWidget::refreshUI()
{
	this->update();
}
