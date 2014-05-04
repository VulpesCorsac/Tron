#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "InitConstants.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include <vector>

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
