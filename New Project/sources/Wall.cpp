#include "stdafx.h"
#include "headers\Wall.h"

void Wall::Modify(const Segment2D < double > &_Segment, const int Player_Number) {
	this->PlayerNumber = Player_Number;
	this->Segment = _Segment;
	return;
}

void Wall::Prolong(const Point2D < double > Point) {
	Segment2D < double > Temp(this->Segment.A, Point);
	Modify(Temp, this->PlayerNumber);
	return;
}

Wall::Wall(const Segment2D < double > &_Segment, const int Player_Number) {
	Modify(_Segment, this->PlayerNumber);
}

Wall::~Wall(void) {

}

Wall &Wall::operator = (const Wall &_Wall) {
	if (this == &_Wall)
		return *this;
	this->Segment = _Wall.Segment;
	this->PlayerNumber = _Wall.PlayerNumber;
	return *this;
}

bool operator == (const Wall &Wall1, const Wall &Wall2) {
	return (Wall1.PlayerNumber == Wall2.PlayerNumber &&
		    Wall1.Segment == Wall2.Segment);
}

bool operator != (const Wall &Wall1, const Wall &Wall2) {
	return (!(Wall1 == Wall2));
}
