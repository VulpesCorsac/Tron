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
	bool Wall_Modify(const int &n, const Wall &New_Wall);
	bool Wall_Modify(const Wall &_Wall, const Wall &New_Wall);
	bool Wall_Modify(const vector < Wall > &Walls, const vector < Wall > &New_Walls);

	void Bonus_Add(const Bonus &_Bonus);
	void Bonus_Add(const vector < Bonus > &Bonuses);
	bool Bonus_Delete(const int &n);
	bool Bonus_Delete(const Bonus &_Bonus);
	bool Bonus_Delete(const vector < Bonus > &Bonuses);

	void PLayer_Kill(const int &Player_number);
	bool Player_Turn(const int &Player_number); // TO DO:
	bool Player_Add(const Player &Player); // TO DO:

	void UPD(); // TO DO:

};

#endif // GAME_ENGINE_H_INCLUDED
