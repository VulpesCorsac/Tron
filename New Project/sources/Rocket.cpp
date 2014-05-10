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

Rocket &Rocket::operator = (const Rocket &_Rocket) {
	if (this == &_Rocket)
		return *this;
	this->Current_Point = _Rocket.Current_Point;
	this->Direction = _Rocket.Direction;
	this->Length = _Rocket.Length;
	this->Speed = _Rocket.Speed;
	this->Start_Point = _Rocket.Start_Point;
	return *this;
}

bool operator == (const Rocket &Rocket1, const Rocket &Rocket2) {
	return (ABS(Rocket1.Length - Rocket2.Length) <= EPS &&
		    ABS(Rocket1.Speed - Rocket2.Speed) <= EPS &&
		    Norm(Rocket1.Direction) == Norm(Rocket2.Direction) &&
		    Rocket1.Start_Point == Rocket2.Start_Point);
}

bool operator != (const Rocket &Rocket1, const Rocket &Rocket2) {
	return (!(Rocket1 == Rocket2));
}
