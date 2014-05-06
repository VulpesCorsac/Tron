#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "stdafx.h"

class Game {
public:
    // All constants
    Init_Constants Constants;

	// Players Ammount
	int Players_Ammount;

	// All Players
	vector < Player > Players;

	// All Walls
	vector < Wall > Walls;

	//All Bombs
	vector < Bomb > Bombs;

	//All Rockets
	vector < Rocket > Rockets;
};

#endif // GAME_H_INCLUDED
