#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "Game.h"

class Game_Engine {
private:
	// Converts from game classes to polygon
	Polygon2D < double > Polygon_from_cycle(const LightCycle &Cycle);
	Polygon2D < double > Polygon_from_wall(const Wall &Segment);

	// Intersect polygon in turning
	bool Intersect_in_turning(const Polygon2D < double > &Turned, const Polygon2D < double > &Static, const double &alpha);

public:
	// Data	
	Init_Constants* Constants; // All constants
	Game Current_Game; // Game itself

};

#endif // GAME_ENGINE_H_INCLUDED
