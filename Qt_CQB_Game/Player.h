#pragma once
class Player
{
public:
	Player();
	~Player();

	//������ʶ�����id
	unsigned int player_id;
	bool visibility = false;//��������ҿɼ���
	//��Ӫ
	unsigned int team;
	//��ǰ״̬
	double pos_x;//��ɫĿǰλ��
	double pos_y;
	double fov = 65;//��Ұ
	double facing;//Ŀǰ������
	bool bleeding;
	bool leg_hurted;
	bool arm_hurted;

	//��ʱ�����Ϊ
	bool behavior_move_ahead;
	bool behavior_move_back;
	bool behavior_move_left;
	bool behavior_move_right;
	bool behavior_move_speedUp;
	bool behavior_engage_shooting;//������Ϊ
private:

};

