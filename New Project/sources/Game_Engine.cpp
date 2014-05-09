#include "stdafx.h"
#include "headers\Game_Engine.h"

Polygon2D < double > Game_Engine::Polygon_from_cycle(const LightCycle &Cycle) {
	return Polygon2D < double >();
}

Polygon2D < double > Game_Engine::Polygon_from_wall(const Wall &Segment) {
	return Polygon2D < double >();
}

bool Game_Engine::Intersect_in_turning(const Polygon2D < double > &Turning, const Point2D < double > &TurnOf,const Polygon2D < double > &Static, const double &alpha) {
	Polygon2D < double > Turned = Turning;
	double d_alpha = alpha/(2*this->Constants->LightCycle_Length/this->Constants->LightCycle_Width);
	for (double temp = 0; temp <= alpha; temp += d_alpha) {
		if (Cross_polygon(Turned, Static))
			return true;
		Turned = turn(Turning, TurnOf, temp);
	}
	return false;
}

bool Game_Engine::Intersect(const LightCycle &Cycle, const Wall &_Wall) {
	return Cross_polygon(Polygon_from_cycle(Cycle), Polygon_from_wall(_Wall));
}

bool Game_Engine::Intersect(const LightCycle &Cycle1, const LightCycle &Cycle2) {
	return Cross_polygon(Polygon_from_cycle(Cycle1), Polygon_from_cycle(Cycle2));
}