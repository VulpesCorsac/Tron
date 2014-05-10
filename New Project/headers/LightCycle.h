#ifndef LIGHTCYCLE_H_INCLUDED
#define LIGHTCYCLE_H_INCLUDED

#include "stdafx.h"

class LightCycle {
public:
    Point2D < double > Current_Point;
    Vector2D < double > Direction;
	double Speed;
	
	//Placing the bike
	void Place(const Point2D < double > &Start_Point, const Vector2D < double > &Dir, const double &_Speed);

	// UPD
	void UPD(const double &dt);

	// Turn
	void Turn(const double &aplha);
	void Turn(const bool &is_left_turn);

	// Update speed
	void SpeedUp(const double &New_Speed);

	LightCycle(const Point2D < double > &Start_Point, const Vector2D < double > &Dir, const double &_Speed);
	LightCycle(void);
	~LightCycle(void);

	LightCycle &operator = (const LightCycle &Cycle);
	friend bool operator == (const LightCycle &Cycle1, const LightCycle &Cycle2);
	friend bool operator != (const LightCycle &Cycle1, const LightCycle &Cycle2);

};

#endif // LIGHTCYCLE_H_INCLUDED
