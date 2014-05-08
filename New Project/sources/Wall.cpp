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