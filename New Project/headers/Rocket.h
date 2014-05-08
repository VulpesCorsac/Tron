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
	void Shoot(const Point2D < double > &Start, const Vector2D < double > &Dir, const double &_Speed, const double &Len);
	
	// UPD
	void UPD(const double &dt);

	// Explode
	bool Explode(void);

	Rocket(const Point2D < double > &Start, const Vector2D < double > &Dir, const double &_Speed, const double &Len);
	~Rocket(void);
};

#endif // ROCKET_H_INCLUDED
