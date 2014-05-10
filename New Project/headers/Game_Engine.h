#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "Game.h"

class Game_Engine {
private:
	// Converts from game classes to polygon
	Polygon2D < double > Polygon_from(const Point2D < double > &C_p, const Vector2D < double > &V, const double w);
	Polygon2D < double > Polygon_from_cycle(const LightCycle &Cycle);
	Polygon2D < double > Polygon_from_wall(const Wall &_Wall);

	// Intersects
	bool Intersect(const LightCycle &Cycle, const Wall &_Wall);
	bool Intersect(const LightCycle &Cycle, const Bomb &_Bomb);
	bool Intersect(const LightCycle &Cycle, const Rocket &_Rocket);
	bool Intersect(const LightCycle &Cycle1, const LightCycle &Cycle2);
	bool Intersect(const Wall &_Wall, const Bomb &_Bomb);
	bool Intersect(const Wall &_Wall, const Rocket &_Rocket);

public:
	// Data	
	Init_Constants* Constants; // All constants
	Game Current_Game; // Game itself
	
	// Changes
	void Bomb_Add(const Bomb &_Bomb);
	void Bomb_Add(const vector < Bomb > &Bombs);
	bool Bomb_Delete(const int &n);
	bool Bomb_Delete(const Bomb &_Bomb);
	bool Bomb_Delete(const vector < Bomb > &Bombs);
	bool Bomb_Explosion(); // TO DO:

	void Rocket_Add(const Rocket &_Rocket);
	void Rocket_Add(const vector < Rocket > &Rockets);
	bool Rocket_Delete(const int &n);
	bool Rocket_Delete(const Rocket &_Rocket);
	bool Rocket_Delete(const vector < Rocket > &Rockets);
	bool Rocket_Explosion(); // TO DO:

	void Wall_Add(const Wall &_Wall);
	void Wall_Add(const vector < Wall > &Walls);
	bool Wall_Modify(const int &n); // TO DO:
	bool Wall_Modify(const Wall &_Wall); // TO DO:
	bool Wall_Modify(const vector < Wall > &Walls); // TO DO:

	void Kill_PLayer(const int &Player_number);
	bool Turn_Player(const int &Player_number); // TO DO:
	bool Add_Player(const Player &Player); // TO DO:

	void UPD(); // TO DO:

};

#endif // GAME_ENGINE_H_INCLUDED
