#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "Game.h"

class Game_Engine {
private:
	// Converts from game classes to polygon
	Polygon2D < double > Polygon_from_cycle(const LightCycle &Cycle);
	Polygon2D < double > Polygon_from_wall(const Wall &Segment);

	// Intersects
	bool Intersect_in_turning(const Polygon2D < double > &Turning, const Point2D < double > &TurnOf, const Polygon2D < double > &Static, const double &alpha);
	bool Intersect(const LightCycle &Cycle, const Wall &_Wall);
	bool Intersect(const LightCycle &Cycle1, const LightCycle &Cycle2);

public:
	// Data	
	Init_Constants* Constants; // All constants
	Game Current_Game; // Game itself

};

#endif // GAME_ENGINE_H_INCLUDED
