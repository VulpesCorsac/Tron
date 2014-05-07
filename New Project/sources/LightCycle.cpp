#include "stdafx.h"
#include "headers\LightCycle.h"

void LightCycle::Place(Point2D < double > Start_Point, Vector2D < double > Dir, double _Speed) {
	this->Current_Point = Start_Point;
	this->Direction = Dir;
	this->Speed = _Speed;
}

void LightCycle::UPD(double dt) {
	this->Current_Point += (dt*this->Speed)*Norm(this->Direction);
}

void LightCycle::Turn(double alpha) {
	this->Direction = turn(this->Direction, this->Current_Point, alpha);
}

void LightCycle::Turn(bool is_left_turn) {
	if (is_left_turn)
		this->Direction = turn(this->Direction, this->Current_Point,  0.5*PI < double > ());
	else
		this->Direction = turn(this->Direction, this->Current_Point, -0.5*PI < double >());
}

LightCycle::LightCycle(Point2D < double > Start_Point, Vector2D < double > Dir, double _Speed) {
	Place(Start_Point, Dir, _Speed);
}

LightCycle::~LightCycle() {

}