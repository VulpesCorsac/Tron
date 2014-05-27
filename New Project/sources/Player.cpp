#include "stdafx.h"
#include "headers\Player.h"

void Player::Kill(void) {
	this->Alive = false;
	this->MyCycle = LightCycle(Point2D < double > (-100, -100), Vector2D < double > (0, 0), 0);
	return;
}

void Player::Gotta_Bomb(void) {
	this->Bomb_Ammount++;
	return;
}

void Player::Gotta_Rocket(void) {
	this->Rocket_Ammount++;
	return;
}

Bomb Player::Place_Bomb(void) {
	assert(this->Bomb_Ammount > 0);
	return Bomb(this->MyCycle.Current_Point, this->Constants->Bomb_Time, this->Constants->Bomb_Radius);
}

Rocket Player::Shoot_Rocket(void) {
	assert(this->Rocket_Ammount > 0);
	return Rocket(this->MyCycle.Current_Point, this->MyCycle.Direction, this->Constants->Rocket_Speed, this->Constants->Rocket_Speed, this->Constants->Rocket_Radius);
}

void Player::UPD(const double &dt) {
	this->MyCycle.UPD(dt);
	return;
}

void Player::Turn(const double &aplha) {
	this->MyCycle.Turn(aplha);
	return;
}

void Player::Turn(const bool &is_left_turn) {
//	this->MyCycle.Current_Point += (this->Constants->LightCycle_Width * 0.6) * this->MyCycle.Direction;
	this->MyCycle.Turn(is_left_turn);
	this->MyCycle.Current_Point += (this->Constants->LightCycle_Width * 0.6) * this->MyCycle.Direction;
	return;
}

void Player::SpeedUp(const double &New_Speed) {
	this->MyCycle.SpeedUp(New_Speed);
	return;
}

Player::Player(const Point2D < double > &St_Point, const Vector2D < double > &St_Direction, Init_Constants* _Constants) {
	this->Constants = _Constants;
	this->Alive = true;
	this->Bomb_Ammount = this->Constants->Bomb_Default_Ammount;
	this->Rocket_Ammount = this->Constants->Rocket_Default_Ammount;
	this->MyCycle.Place(St_Point, St_Direction, this->Constants->LightCycle_DefaultSpeed);
}

Player::Player() {

}

Player::~Player() {

}

Player& Player::operator = (const Player &Player1) {
	if (this == &Player1)
		return *this;
	this->MyCycle = Player1.MyCycle;
	this->Alive = Player1.Alive;
	this->Bomb_Ammount = Player1.Bomb_Ammount;
	this->Constants = Player1.Constants;
	this->Player_Number = Player1.Player_Number;
	this->Rocket_Ammount = Player1.Rocket_Ammount;
	this->Team_Number = Player1.Team_Number;
	return *this;
}

bool operator == (const Player &Player1, const Player &Player2) {
	if (Player1.Alive != Player2.Alive)
		return false;
	if (Player1.Bomb_Ammount != Player2.Bomb_Ammount)
		return false;
	if (Player1.Constants != Player2.Constants)
		return false;
	if (Player1.MyCycle != Player2.MyCycle)
		return false;
	if (Player1.Player_Number != Player2.Player_Number)
		return false;
	if (Player1.Rocket_Ammount != Player2.Rocket_Ammount)
		return false;
	if (Player1.Team_Number != Player2.Team_Number)
		return false;
	return true;
}

bool operator != (const Player &Player1, const Player &Player2) {
	return (!(Player1 == Player2));
}