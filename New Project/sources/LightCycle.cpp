#include "stdafx.h"
#include "headers\LightCycle.h"

void LightCycle::Place(const Point2D < double > &Start_Point, const Vector2D < double > &Dir, const double &_Speed) {
	this->Current_Point = Start_Point;
	this->Direction = Dir;
	this->Speed = _Speed;
	return;
}

void LightCycle::UPD(const double &dt) {
	this->Current_Point += (dt*this->Speed)*Norm(this->Direction);
	return;
}

void LightCycle::Turn(const double &alpha) {
	this->Direction = turn(this->Direction, this->Current_Point, alpha);
	return;
}

void LightCycle::Turn(const bool &is_left_turn) {
	if (is_left_turn)
		this->Direction = turn(this->Direction, this->Current_Point,  0.5*PI < double > ());
	else
		this->Direction = turn(this->Direction, this->Current_Point, -0.5*PI < double >());
}

void LightCycle::SpeedUp(const double &New_Speed) {
	this->Speed = New_Speed;
	return;
}

LightCycle::LightCycle(const Point2D < double > &Start_Point, const Vector2D < double > &Dir, const double &_Speed) {
	Place(Start_Point, Dir, _Speed);
}

LightCycle::LightCycle(void) {

}

LightCycle::~LightCycle(void) {

}

LightCycle &LightCycle::operator = (const LightCycle &Cycle) {
	if (this == &Cycle)
		return *this;
	this->Current_Point = Cycle.Current_Point;
	this->Direction = Cycle.Direction;
	this->Speed = Cycle.Speed;
	return *this;

}

bool operator == (const LightCycle &Cycle1, const LightCycle &Cycle2) {
	return (Cycle1.Current_Point == Cycle2.Current_Point &&
		    Norm(Cycle1.Direction) == Norm(Cycle2.Direction) &&
		    ABS(Cycle1.Speed - Cycle2.Speed) <= EPS);
}

bool operator != (const LightCycle &Cycle1, const LightCycle &Cycle2) {
	return (!(Cycle1 == Cycle2));
}
