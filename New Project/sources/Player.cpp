#include "stdafx.h"
#include "headers\Player.h"

void Player::Kill(void) {
	this->Alive = false;
	this->MyCycle = LightCycle();
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
	this->MyCycle.Turn(is_left_turn);
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

