#include "GameWidget.h"
#include <iostream>
#include <QPainter>
#include "algorithm.h"
using namespace std;
GameWidget::GameWidget(QWidget *parent,GameMap * map, Player * player_self,GameServer * gameServer)
	: QWidget(parent)
{
	count = 0;
	this->grabKeyboard();//ʹ���ڿ��Բ�׽����
	setMouseTracking(true);//���������ɴ�������ƶ��¼�
	
	//��ʼ��ǰ�˽���
	Player_yourself = player_self;
	this->map = map;
	this->server = gameServer;
	//���ý���ˢ��Ϊ100hz
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameWidget::refreshUI);
	timer->start(1000 / 100);
	ui.setupUi(this);
}


//drawing event
void GameWidget::paintEvent(QPaintEvent *)
{
	//paintevent�Ḳ�ǵ�stylesheet����ʽ����Ҫ�����⼸�䣬Qframeû�������
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	/********************************************************/
	QPainter painter(this);
	QPen pen; //����
	pen.setColor(QColor(255, 255, 255));
	pen.setWidth(3);
	painter.setPen(pen);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	//���Ƶ�ͼ
	for (int i = 0; i < map->walls.size(); i++)
	{
		painter.drawLine(map->walls[i].startPoint, map->walls[i].endPoint);
	}

	//�������
	pen.setColor(QColor(255, 255, 0));
	pen.setWidth(1);
	painter.setPen(pen);
	painter.drawEllipse(QRectF(Player_yourself->pos_x-10, Player_yourself->pos_y-10,20,20));


	//������Ұ���������
	pen.setColor(QColor(255, 40, 40));
	pen.setWidth(1);
	painter.setPen(pen);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	for (int i = 0; i < 12; i++)
	{
		if (server->playerVisualMap[Player_yourself->player_id][i].visibility)
		{
			painter.drawEllipse(QRectF(server->playerVisualMap[Player_yourself->player_id][i].pos_x - 10, 
				server->playerVisualMap[Player_yourself->player_id][i].pos_y - 10, 20, 20));
		}
	}
	//���ƽ�������
	//DEBUG_
	DEBUG_DrawVisualLines();
	DEBUG_DrawVisionBorders(Player_yourself);
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

void GameWidget::mouseMoveEvent(QMouseEvent * e)
{	
	//e->globalPos() �ǻ�ȡ������������Ļ������	
	Player_yourself->facingVec_x = e->pos().x();
	Player_yourself->facingVec_y = e->pos().y();
	Player_yourself->facingAngle = algo_getLineAngle(QPointF(Player_yourself->pos_x, Player_yourself->pos_y), e->pos());
	//cout << "current aiming angle: " << Player_yourself->facingAngle << endl;
}

void GameWidget::refreshUI()
{
	this->update();

}

void GameWidget::DEBUG_DrawVisualLines()
{
	QPainter painter(this);
	QPen pen; //����
	pen.setColor(QColor(255, 0, 200));
	pen.setWidth(1);
	painter.setPen(pen);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	for (int i = 0; i < 12; i++)
	{
		if (server->playerVisualMap[Player_yourself->player_id][i].visibility)
		{
			//middle
			painter.drawLine(QPointF(Player_yourself->pos_x,Player_yourself->pos_y),
							  QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x, server->playerVisualMap[Player_yourself->player_id][i].pos_y));
			//u
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x , server->playerVisualMap[Player_yourself->player_id][i].pos_y - PLAYER_SIZE));
			//ru
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x + PLAYER_SIZE/sqrt(2), server->playerVisualMap[Player_yourself->player_id][i].pos_y - PLAYER_SIZE / sqrt(2)));
			//r
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x + PLAYER_SIZE, server->playerVisualMap[Player_yourself->player_id][i].pos_y));
			//rd
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x + PLAYER_SIZE / sqrt(2), server->playerVisualMap[Player_yourself->player_id][i].pos_y + PLAYER_SIZE / sqrt(2)));
			//d
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x, server->playerVisualMap[Player_yourself->player_id][i].pos_y + PLAYER_SIZE));
			//ld
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x - PLAYER_SIZE / sqrt(2), server->playerVisualMap[Player_yourself->player_id][i].pos_y + PLAYER_SIZE / sqrt(2)));
			//l
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x - PLAYER_SIZE, server->playerVisualMap[Player_yourself->player_id][i].pos_y));
			//lu
			painter.drawLine(QPointF(Player_yourself->pos_x, Player_yourself->pos_y),
				QPointF(server->playerVisualMap[Player_yourself->player_id][i].pos_x - PLAYER_SIZE / sqrt(2), server->playerVisualMap[Player_yourself->player_id][i].pos_y - PLAYER_SIZE / sqrt(2)));
		}
	}

}

//������Ұ�߽�
void GameWidget::DEBUG_DrawVisionBorders(Player * player)
{
	QPainter painter(this);
	QPen pen; //����
	pen.setColor(QColor(0, 255, 255));
	pen.setWidth(1);
	painter.setPen(pen);
	painter.drawLine(QPointF(player->pos_x, player->pos_y),
		algo_rotateLineByAngle(QPointF(player->pos_x, player->pos_y),
			QPointF(player->facingVec_x, player->facingVec_y), -M_PI / 6,1500));
	painter.drawLine(QPointF(player->pos_x, player->pos_y),
		algo_rotateLineByAngle(QPointF(player->pos_x, player->pos_y),
			QPointF(player->facingVec_x, player->facingVec_y), +M_PI / 6, 1500));
}