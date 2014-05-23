#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "stdafx.h"

class Wall {
public:
    Segment2D < double > Segment;
    int Player_Number;
	int Wall_Number;

	// Modify a wall
	void Modify(const Segment2D < double > &_Segment, const int &PlayerNumber, const int &WallNumber = -1);
	void Prolong(const Point2D < double > Point);

	Wall(const Segment2D < double > &_Segment, const int &PlayerNumber, const int &WallNumber = -1);
	~Wall();

	Wall &operator = (const Wall &_Wall);
	friend bool operator == (const Wall &Wall1, const Wall &Wall2);
	friend bool operator != (const Wall &Wall1, const Wall &Wall2);

};

bool Equal(Wall Wall1, Wall Wall2); // Do not match Wall_Number

#endif // WALL_H_INCLUDED