#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "Game.h"

bool WallComparator(Wall &Wall1, Wall &Wall2);

class Game_Engine {
private:
	// Helpful
	int round(const double &x) const;
	void WallSort(const int &n1);
	void WallSort(const int &n1, const int &n2);

	// Converts from game classes to polygon
	Polygon2D < double > Polygon_from(const Point2D < double > &C_p, const Vector2D < double > &V, const double &w);
	Polygon2D < double > Polygon_from_cycle(const LightCycle &Cycle);
	Polygon2D < double > Polygon_from_wall(const Wall &_Wall);

	// Intersects
	bool Intersect(const LightCycle &Cycle, const Wall &_Wall);
	bool Intersect(const LightCycle &Cycle, const Bomb &_Bomb);
	bool Intersect(const LightCycle &Cycle, const Rocket &_Rocket);
	bool Intersect(const LightCycle &Cycle1, const LightCycle &Cycle2);
	bool Intersect(const Player &_Player, const Bomb &_Bomb);
	bool Intersect(const Player &_Player, const Rocket &_Rocket);
	bool Intersect(const Player &_Player1, const Player &_Player2);
	 int Intersect_Tails(const Player &_Player1, const Player &_Player2, const double &dt);
	bool Intersect_Walls_Not_Tails(const Player &_Player,const double &dt);
	bool Intersect(const Wall &_Wall, const Bomb &_Bomb);
	bool Intersect(const Wall &_Wall, const Rocket &_Rocket);
	bool Intersect(const Rocket &_Rocket, const double &dt);
	bool Intersect(const Polygon2D < double > &P1, const Polygon2D < double > &P2);
	bool Intersect(const Player &_Player, const Bonus &_Bonus, const double &dt);

	void Make_some_magic(const Circle < double > &C, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls);
	bool Out_of_Field(const Player &_Player, const double &dt);

	void Bomb_Add(const Bomb &_Bomb);
	void Bomb_Add(const vector < Bomb > &Bombs);
	bool Bomb_Delete(const int &n);
	bool Bomb_Delete(const Bomb &_Bomb);
	bool Bomb_Delete(const vector < int >  &Bombs);
	bool Bomb_Delete(const vector < Bomb > &Bombs);
	void Bomb_Explosion(const int &Bomb_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls);

	void Rocket_Add(const Rocket &_Rocket);
	void Rocket_Add(const vector < Rocket > &Rockets);
	bool Rocket_Delete(const int &n);
	bool Rocket_Delete(const Rocket &_Rocket);
	bool Rocket_Delete(const vector < int >  &Rockets);
	bool Rocket_Delete(const vector < Rocket > &Rockets);
	void Rocket_Explosion(const int &Rocket_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls);

	bool Wall_Modify(const int &n, const Wall &New_Wall);
	bool Wall_Modify(const Wall &_Wall, const Wall &New_Wall);
	bool Wall_Modify(const vector < pair < Wall, Wall > > &Walls);
	bool Wall_Add(const Wall &_Wall);
	bool Wall_Add(const vector < Wall > &Walls);
	bool Wall_Delete(const int &n);
	bool Wall_Delete(const Wall &_Wall);
	bool Wall_Delete(const vector < int >  &Walls);
	bool Wall_Delete(const vector < Wall > &Walls);
	bool Wall_Delete_flag(const int &n);
	bool Wall_Delete_flag(const Wall &_Wall);
	bool Wall_Delete_flag(const vector < Wall > &Walls);
	bool Wall_Delete_flag(const vector < int >  &Walls);
	bool Wall_Parse(const vector < pair < Wall, Wall > > &Walls);

	void Bonus_Add(const Bonus &_Bonus);
	void Bonus_Add(const vector < Bonus > &Bonuses);
	bool Bonus_Delete(const int &n);
	bool Bonus_Delete(const Bonus &_Bonus);
	bool Bonus_Delete(const vector < int >   &Bonuses);
	bool Bonus_Delete(const vector < Bonus > &Bonuses);


	Player Player_Generate(void);
	vector < Player > Player_Generate(const int &n);
	void Player_Add(Player &_Player);
	void Player_Add(vector < Player > &Players);
	void PLayer_Kill(const int &Player_number);
	void PLayer_Kill(const vector < int > &Players_Numbers);

public:
	// Data
	Init_Constants* Constants;
	Game Current_Game;
	int Veryfied_Walls;
	State Game_State;
	Changes Game_Changes;

	vector < Bomb > Exploded_Bomb;
	vector < Rocket > Exploded_Rocket;

	// Changes
	void Bomb_Place(const int &Player_number);
	void Rocket_Place(const int &Player_number);
	void Bonus_Place(void);


	bool Wall_Prolong(const int &n);
	bool Wall_Prolong_All(void);

	void Player_Turn(const int &Player_number, const bool &left_turn);
	void PLayer_Turn_Client(const int &Player_number, const bool &left_turn);

	void _UPD(const double dt, State &St, Changes &Ch);
	void _UPD_Client(const double dt, State &St, Changes &Ch, bool noBombs);
	void UPD(const double dt);
	void UPD_Client(const double dt, bool noBombs = false);

	bool Game_Over(int &Win_Team); // returns -1 when all are dead

	void Get_Changes_ACC(Changes &Ch);
	void Update_Changes_ACC(const Changes &Ch); //TODO:
	void Get_Changes_NACC(State &St);
	void Update_Changes_NACC(const State &St);
	void Start_Game(const int &_Players_Ammount, State &St);
	void Start_Game_Client(const State &St);
};

#endif // GAME_ENGINE_H_INCLUDED
