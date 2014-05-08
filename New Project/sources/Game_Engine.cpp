#include "stdafx.h"
#include "headers\Game_Engine.h"

bool Game_Engine::Intersect_in_turning(const Polygon2D < double > &Turning, const Polygon2D < double > &Static, const double &alpha) {
	Polygon2D < double > Turned = Turning;
	double d_alpha = alpha/(2*this->Constants->LightCycle_Length/this->Constants->LightCycle_Width);
	for (double temp = 0; temp <= alpha; temp += d_alpha) {
		if (Cross_polygon(Turned, Static))
			return true;
		Turned = turn(Turning, temp);
	}
	return false;
}

Polygon2D < double > Game_Engine::Polygon_from_cycle(const LightCycle &Cycle) {
	return Polygon2D < double > ();
}

Polygon2D < double > Game_Engine::Polygon_from_wall(const Wall &Segment) {
	return Polygon2D < double > ();
}
