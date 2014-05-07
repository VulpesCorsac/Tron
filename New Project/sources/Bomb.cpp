#include "stdafx.h"
#include "headers\Bomb.h"

void Bomb::Place(Point2D < double > Point, double Time_Left, double _R) {
	this->Time_for_explosion = Time_Left;
	this->Current_Point = Point;
	this->Radius = _R;
}

void Bomb::UPD(double dt) {
	this->Time_for_explosion -= dt;
}

bool Bomb::Explode() {
	return (this->Time_for_explosion <= 0);
}

Bomb::Bomb(Point2D < double > Point, double Time_Left, double _R) {
	Place(Point, Time_Left, _R);
}

Bomb::~Bomb() {

}