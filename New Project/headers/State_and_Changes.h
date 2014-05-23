#ifndef STATE_AND_CHANGES_H_INCLUDED
#define STATE_AND_CHANGES_H_INCLUDED

#include "stdafx.h"
#include "Server.h"

struct State {
	vector < Player > Players;
};

bool operator == (const State &State1, const State &State2);
bool operator != (const State &State1, const State &State2);
State operator + (const State &State1, const State &State2);
State operator += (State &State1, const State &State2);
void Clear(State &State1);

struct Changes {
	vector < int >                   Killed_Players;
	vector < Wall >                  New_Walls;
	vector < pair < Wall, Wall > >   Modifyed_Walls;
	vector < Bomb >	                 Placed_Bomb;
	vector < int >                   Exploded_Bombs;
	vector < Rocket >                Placed_Rocket;
	vector < int >                   Exploded_Rockets;
	vector < Bonus >                 Placed_Bonuses;
	vector < int >                   Collected_Bonuses;
};

bool operator == (const Changes &Changes1, const Changes &Changes2);
bool operator != (const Changes &Changes1, const Changes &Changes2);
Changes operator + (const Changes &Changes1, const Changes &Changes2);
Changes operator += (Changes &Changes1, const Changes &Changes2);
void Clear(Changes &Changes1);

#endif // STATE_AND_CHANGES_H_INCLUDED