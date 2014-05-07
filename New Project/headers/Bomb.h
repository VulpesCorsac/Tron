#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include "stdafx.h"

class Bomb {
public:
	Point2D < double > Current_Point;
	double Time_for_explosion;
	double Radius;

	// Place bomb
	void Place(Point2D < double > Point, double Time_Left, double _R);

	// UPD
	void UPD(double dt);
	
	// Explode
	bool Explode();

	Bomb(Point2D < double > Point, double Time_Left, double _R);
	~Bomb();
};

#endif // BOMB_H_INCLUDED
