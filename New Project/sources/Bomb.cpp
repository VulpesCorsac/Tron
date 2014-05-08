#include "stdafx.h"
#include "headers\Bomb.h"

void Bomb::Place(const Point2D < double > &Point, const double &Time_Left, const double &_R) {
	this->Time_for_explosion = Time_Left;
	this->Current_Point = Point;
	this->Radius = _R;
	return;
}

void Bomb::UPD(const double &dt) {
	this->Time_for_explosion -= dt;
	return;
}

bool Bomb::Explode(void) {
	return (this->Time_for_explosion <= 0);
}

Bomb::Bomb(const Point2D < double > &Point, const double &Time_Left, const double &_R) {
	Place(Point, Time_Left, _R);
}

Bomb::~Bomb(void) {

}