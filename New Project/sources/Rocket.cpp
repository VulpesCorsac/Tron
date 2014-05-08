#include "stdafx.h"
#include "headers\Rocket.h"

void Rocket::Shoot(const Point2D < double > &Start, const Vector2D < double > &Dir, const double &_Speed, const double &Len) {
	this->Start_Point = Start;
	this->Current_Point = Start;
	this->Direction = Dir;
	this->Speed = _Speed;
	this->Length = Len;
}

void Rocket::UPD(const double &dt) {
	this->Current_Point += (dt*this->Speed)*Norm(this->Direction);
}

bool Rocket::Explode(void) {
	return (dist(this->Start_Point, this->Current_Point) >= this->Length);
}

Rocket::Rocket(const Point2D < double > &Start, const Vector2D < double > &Dir, const double &_Speed, const double &Len) {
	Shoot(Start, Dir, _Speed, Len);
}

Rocket::~Rocket(void) {

}