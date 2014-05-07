#include "stdafx.h"
#include "headers\Rocket.h"

void Rocket::Shoot(Point2D < double > Start, Vector2D < double > Dir, double _Speed, double Len) {
	this->Start_Point = Start;
	this->Current_Point = Start;
	this->Direction = Dir;
	this->Speed = _Speed;
	this->Length = Len;
}

void Rocket::UPD(double dt) {
	this->Current_Point += (dt*this->Speed)*Norm(this->Direction);
}

bool Rocket::Explode() {
	return (dist(this->Start_Point, this->Current_Point) >= this->Length);
}

Rocket::Rocket(Point2D < double > Start, Vector2D < double > Dir, double _Speed, double Len) {
	Shoot(Start, Dir, _Speed, Len);
}

Rocket::~Rocket() {

}