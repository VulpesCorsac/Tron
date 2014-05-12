#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "stdafx.h"

class Wall {
public:
    Segment2D < double > Segment;
    int PlayerNumber;

	// Modify a wall
	void Modify(const Segment2D < double > &_Segment, const int Player_Number);
	void Prolong(const Point2D < double > Point);

	Wall(const Segment2D < double > &_Segment, const int Player_Number);
	~Wall();

	Wall &operator = (const Wall &_Wall);
	friend bool operator == (const Wall &Wall1, const Wall &Wall2);
	friend bool operator != (const Wall &Wall1, const Wall &Wall2);

};

#endif // WALL_H_INCLUDED
