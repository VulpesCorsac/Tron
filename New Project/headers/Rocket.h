#ifndef ROCKET_H_INCLUDED
#define ROCKET_H_INCLUDED

#include "stdafx.h"

class Rocket {
public:
	Point2D < double > Current_Point;
	Point2D < double > Start_Point;
	Vector2D < double > Direction;
	double Speed;
	double Length;
	
	// Shoot
	void Shoot(Point2D < double > Start, Vector2D < double > Dir, double _Speed, double Len);
	
	// UPD
	void UPD(double dt);

	// Explode
	bool Explode();

	Rocket(Point2D < double > Start, Vector2D < double > Dir, double _Speed, double Len);
	~Rocket();
};

#endif // ROCKET_H_INCLUDED
