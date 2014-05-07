#ifndef LIGHTCYCLE_H_INCLUDED
#define LIGHTCYCLE_H_INCLUDED

#include "stdafx.h"

class LightCycle {
public:
    Point2D < double > Current_Point;
    Vector2D < double > Direction;
	double Speed;
	
	//Placing the bike
	void Place(Point2D < double > Start_Point, Vector2D < double > Dir, double _Speed);

	// UPD
	void UPD(double dt);

	// Turn
	void Turn(double aplha);
	void Turn(bool is_left_turn);

	LightCycle(Point2D < double > Start_Point, Vector2D < double > Dir, double _Speed);
	~LightCycle();

};

#endif // LIGHTCYCLE_H_INCLUDED
