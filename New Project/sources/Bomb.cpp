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

Bomb::Bomb (Bomb *a)
{
	this->Current_Point = a->Current_Point;
	this->Owner = a->Owner;
	this->Radius = a->Radius;
	this->Time_for_explosion = a->Time_for_explosion;
}


Bomb &Bomb::operator = (const Bomb &_Bomb) {
	if (this == &_Bomb)
		return *this;
	this->Current_Point = _Bomb.Current_Point;
	this->Radius = _Bomb.Radius;
	this->Time_for_explosion = _Bomb.Time_for_explosion;
	return *this;
}

bool operator == (const Bomb &Bomb1, const Bomb &Bomb2) {
	return (Bomb1.Current_Point == Bomb2.Current_Point &&
		ABS(Bomb1.Radius - Bomb2.Radius) <= EPS &&
		ABS(Bomb1.Time_for_explosion - Bomb2.Time_for_explosion) <= EPS);
}

bool operator != (const Bomb &Bomb1, const Bomb &Bomb2) {
	return (!(Bomb1 == Bomb2));
}
