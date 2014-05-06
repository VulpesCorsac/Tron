#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "stdafx.h"

class Player {
	// Current Point and direction
	LightCycle MyCycle;

	// PLayer number
	int Player_Number;
	
	// Team number
	int Team_Number;

	// Alive?
	bool Alive;

	// Bomb ammount
	int Bomb_Ammount;

	// Rocket ammount
	int Rocket_Ammount;

};

#endif // PLAYER_H_INCLUDED
