#pragma once
class Player
{
public:
	Player();
	~Player();

	//服务器识别玩家id
	unsigned int player_id;
	bool visibility = false;//对其他玩家可见性
	//阵营
	unsigned int team;
	//当前状态
	double pos_x;//角色目前位置
	double pos_y;
	double fov = 65;//视野
	double facing;//目前朝向方向
	bool bleeding;
	bool leg_hurted;
	bool arm_hurted;

	//此时玩家行为
	bool behavior_move_ahead;
	bool behavior_move_back;
	bool behavior_move_left;
	bool behavior_move_right;
	bool behavior_move_speedUp;
	bool behavior_engage_shooting;//开火行为
private:

};

