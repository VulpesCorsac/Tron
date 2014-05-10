#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "stdafx.h"

class Bonus {
public:
	Point2D < double > Point;
	bool Bomb; // Type 1
	bool Rocket; // Type 2

	void Place(const Point2D < double > &_Point, const int &Type);

	Bonus(const Point2D < double > &_Point, const int &Type);
	~Bonus();

	Bonus &operator = (const Bonus &_Bonus);
	friend bool operator == (const Bonus &Bonus1, const Bonus &Bonus2);
	friend bool operator != (const Bonus &Bonus1, const Bonus &Bonus2);
};

#endif // BONUS_H_INCLUDED
