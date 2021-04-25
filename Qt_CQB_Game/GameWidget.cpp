#include "GameWidget.h"
#include <iostream>
#include <QPainter>
using namespace std;
GameWidget::GameWidget(QWidget *parent,GameMap * map, Player * player_self)
	: QWidget(parent)
{
	count = 0;
	this->grabKeyboard();
	Player_yourself = player_self;
	this->map = map;

	//���ý���ˢ��Ϊ45hz
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameWidget::refreshUI);
	timer->start(1000 / 45);
	ui.setupUi(this);
}


//drawing event
void GameWidget::paintEvent(QPaintEvent *)
{
	//cout << "��ͼ�¼������� " << ++count << " ��" << endl;
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

	//���Ƶ�ͼ
	for (int i = 0; i < map->walls.size(); i++)
	{
		painter.drawLine(map->walls[i].startPoint, map->walls[i].endPoint);
	}

	//�������
	pen.setColor(QColor(255, 255, 0));
	pen.setWidth(1);
	painter.setPen(pen);

	painter.drawEllipse(QRectF(Player_yourself->pos_x, Player_yourself->pos_y,20,20));
	//���ƽ�������
}
//key press events
void GameWidget::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_A)
	{
		//cout << "����" << endl;
		Player_yourself->behavior_move_left = true;
	}
	if (e->key() == Qt::Key_D)
	{
		//cout << "����" << endl;
		Player_yourself->behavior_move_right = true;
	}
	if (e->key() == Qt::Key_S)
	{
		//cout << "����" << endl;
		Player_yourself->behavior_move_back = true;
	}
	if (e->key() == Qt::Key_W)
	{
		//cout << "ǰ��" << endl;
		Player_yourself->behavior_move_ahead = true;
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
}

void GameWidget::refreshUI()
{
	this->update();
}
