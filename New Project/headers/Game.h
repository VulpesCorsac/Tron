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
	vector < Bonus > Bonuses; // All Bonuses

	void Clear(void);
	void Start(const vector < Player > &_Players);
};

#endif // GAME_H_INCLUDED
