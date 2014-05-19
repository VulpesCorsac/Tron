#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "Game.h"

//TO DO - do this structers
struct state
{
	int n; // number of players
	float *x, *y; // coord of player x,y
};   // nonaccumulating struct for state of players
struct changes 
{

}; // accumulating struct for changes within walls, bombs, etc

class Game_Engine {
private:
	// Helpful
	int round(const double &x) const;

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
	bool Intersect(const Wall &_Wall, const Bomb &_Bomb);
	bool Intersect(const Wall &_Wall, const Rocket &_Rocket);
	bool Intersect(const Player &_Player, const Bonus &_Bonus, const double &dt);

	void Make_some_magic(const Circle < double > &C, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls) {}; // TO DO:

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
	void Bomb_Explosion(const int &Bomb_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls);

	void Rocket_Add(const Rocket &_Rocket);
	void Rocket_Add(const vector < Rocket > &Rockets);
	bool Rocket_Delete(const int &n);
	bool Rocket_Delete(const Rocket &_Rocket);
	bool Rocket_Delete(const vector < Rocket > &Rockets);
	void Rocket_Explosion(const int &Rocket_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls);

	void Wall_Add(const Wall &_Wall);
	void Wall_Add(const vector < Wall > &Walls);
	bool Wall_Modify(const int &n, const Wall &New_Wall);
	bool Wall_Modify(const Wall &_Wall, const Wall &New_Wall);
	bool Wall_Modify(const vector < Wall > &Walls, const vector < Wall > &New_Walls);
	bool Wall_Delete(const int &n);
	bool Wall_Delete(const Wall &_Wall);
	bool Wall_Delete(const vector < Wall > &Walls);
	bool Wall_Delete_flag(const int &n); // Just set player_num to -1, not deleting them from vector
	bool Wall_Delete_flag(const Wall &_Wall);
	bool Wall_Delete_flag(const vector < Wall > &Walls);

	void Bonus_Add(const Bonus &_Bonus);
	void Bonus_Add(const vector < Bonus > &Bonuses);
	bool Bonus_Delete(const int &n);
	bool Bonus_Delete(const Bonus &_Bonus);
	bool Bonus_Delete(const vector < Bonus > &Bonuses);

	Player Player_Generate(void);
	vector < Player > Player_Generate(const int &n);
	void Player_Turn(const int &Player_number, const bool &left_turn); // TO DO:
	void Player_Add(Player &_Player);
	void Player_Add(vector < Player > &Players);
	void PLayer_Kill(const int &Player_number);

	void UPD(const double &dt); // TO DO:

	// TO BE USED BY VOVA:
	void Turn_Player(int side, int player_num) {}; // TO DO turn player to side (see define in client.h )
	void Do_Step();                             // TO DO advance game on dt( 1/60 sec)

	// Plus, we need structers to store data in 4 functions below
	void Get_Changes_ACC(changes *);    //TO DO getting changes for the last frame
	void Update_Changes_ACC(changes *) {}; //TO DO setting changes for the last frame
	void Get_Changes_NACC(state *);     //TO DO getting players state(coordinates and directions)
	void Update_Changes_NACC(state *) {};  //TO DO setting players state(coordinates and directions)
	void Start_Game(int, state *) {}; //TO DO setting starting positions for players(number of players is the first int), returning them in state *
};

#endif // GAME_ENGINE_H_INCLUDED
