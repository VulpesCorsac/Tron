#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "stdafx.h"

class Game {
public:
    // All constants
    Init_Constants Constants;

	// Players Ammount
	int Players_Ammount;

	// All Players
	std::vector < Player > Players;

	// All Walls
	std::vector < Wall > Walls;
};

#endif // GAME_HPP_INCLUDED
