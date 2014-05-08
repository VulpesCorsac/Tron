#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "stdafx.h"

class Game {
public:
	// Game Data
	int Players_Ammount; // Players Ammount
	vector < Player > Players; // All Players
	vector < Wall > Walls; // All Walls
	vector < Bomb > Bombs; //All Bombs
	vector < Rocket > Rockets; //All Rockets
	
	void Kill_PLayer(const int &Player_number); // Kill Player

};

#endif // GAME_H_INCLUDED
