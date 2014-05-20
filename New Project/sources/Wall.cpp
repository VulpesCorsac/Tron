#include "stdafx.h"
#include "headers\Wall.h"

void Wall::Modify(const Segment2D < double > &_Segment, const int &PlayerNumber, const int &WallNumber) {
	this->Player_Number = PlayerNumber;
	this->Wall_Number = WallNumber;
	this->Segment = _Segment;
	return;
}

void Wall::Prolong(const Point2D < double > Point) {
	Segment2D < double > Temp(this->Segment.A, Point);
	Modify(Temp, this->Player_Number, this->Wall_Number);
	return;
}

Wall::Wall(const Segment2D < double > &_Segment, const int &PlayerNumber, const int &WallNumber) {
	Modify(_Segment, PlayerNumber, WallNumber);
}

Wall::~Wall(void) {

}

Wall &Wall::operator = (const Wall &_Wall) {
	if (this == &_Wall)
		return *this;
	this->Segment = _Wall.Segment;
	this->Player_Number = _Wall.Player_Number;
	return *this;
}

bool operator == (const Wall &Wall1, const Wall &Wall2) {
	return (Wall1.Player_Number == Wall2.Player_Number &&
		    Wall1.Segment == Wall2.Segment &&
			Wall1.Wall_Number == Wall2.Wall_Number);
}

bool operator != (const Wall &Wall1, const Wall &Wall2) {
	return (!(Wall1 == Wall2));
}
