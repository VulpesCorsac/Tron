#include "stdafx.h"
#include "headers\Bonus.h"

void Bonus::Place(const Point2D < double > &_Point, const int &Type) {
	this->Point = _Point;
	this->Bomb = false;
	this->Rocket = false;
	if (Type == 1)
		this->Bomb = true;
	if (Type == 2)
		this->Rocket = true;
	return;
}

Bonus::Bonus(const Point2D < double > &_Point, const int &Type) {
	Place(_Point, Type);
}

Bonus::~Bonus() {

}

Bonus &Bonus::operator = (const Bonus &_Bonus) {
	if (this == &_Bonus)
		return *this;
	this->Point = _Bonus.Point;
	this->Bomb = _Bonus.Bomb;
	this->Rocket = _Bonus.Rocket;
	return *this;
}

bool operator == (const Bonus &Bonus1, const Bonus &Bonus2) {
	return (Bonus1.Bomb == Bonus2.Bomb &&
			Bonus1.Rocket == Bonus2.Rocket &&
			Bonus1.Point == Bonus2.Point);
}

bool operator != (const Bonus &Bonus1, const Bonus &Bonus2) {
	return (!(Bonus1 == Bonus2));
}
