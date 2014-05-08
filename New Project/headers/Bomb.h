#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include "stdafx.h"

class Bomb {
public:
	Point2D < double > Current_Point;
	double Time_for_explosion;
	double Radius;

	// Place bomb
	void Place(const Point2D < double > &Point, const double &Time_Left, const double &_R);

	// UPD
	void UPD(const double &dt);
	
	// Explode
	bool Explode(void);

	Bomb(const Point2D < double > &Point, const double &Time_Left, const double &_R);
	~Bomb(void);
};

#endif // BOMB_H_INCLUDED
