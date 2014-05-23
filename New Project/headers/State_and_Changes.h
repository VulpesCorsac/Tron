#ifndef STATE_AND_CHANGES_H_INCLUDED
#define STATE_AND_CHANGES_H_INCLUDED

#include "stdafx.h"
#include "Server.h"

struct State {
	vector < Player > Players;
};

struct Changes {
	vector < int >    Killed_Players;
	vector < Wall >   New_Walls;
	vector < Wall >   Modifyed_Walls;
	vector < Bomb >   Placed_Bomb;
	vector < int >    Exploded_Bombs;
	vector < Rocket > Placed_Rocket;
	vector < int >    Exploded_Rockets;
};

#endif // STATE_AND_CHANGES_H_INCLUDED