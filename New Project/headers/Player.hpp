#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "LightCycle.hpp"

class Player {
	// Current Point and direction
	LightCycle MyCycle;

	// PLayer number
	int Player_Number;
	
	// Team number
	int Team_Number;

	// Alive?
	bool Alive;

};

#endif // PLAYER_HPP_INCLUDED
