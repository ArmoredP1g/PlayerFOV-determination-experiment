#include"Player.h"

Player::Player()
{
	behavior_move_ahead = false;
	behavior_move_back = false;
	behavior_move_left = false;
	behavior_move_right = false;
	behavior_move_speedUp = false;
	behavior_engage_shooting = false;
}
Player::~Player()
{
}