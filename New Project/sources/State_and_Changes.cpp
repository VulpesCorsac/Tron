#include "stdafx.h"
#include "headers\State_and_Changes.h"

bool operator == (const State &State1, const State &State2) {
	if (State1.Players.size() != State2.Players.size())
		return false;
	for (size_t i = 0; i < State1.Players.size(); i++) {
		if (State1.Players[i] != State2.Players[i])
			return false;
	}
	return true;
}

bool operator != (const State &State1, const State &State2) {
	return (!(State1 == State2));
}

State operator + (const State &State1, const State &State2) {
	return State2;
}

State operator += (State &State1, const State &State2) {
	State1 = State2;
	return State1;
}

void Clear(State &State1) {
	State1.Players.clear();
	return;
}

bool operator == (const Changes &Changes1, const Changes &Changes2) {
	if (Changes1.Killed_Players.size() != Changes2.Killed_Players.size())
		return false;
	if (Changes1.Exploded_Bombs.size() != Changes2.Exploded_Bombs.size())
		return false;
	if (Changes1.Exploded_Rockets.size() != Changes2.Exploded_Rockets.size())
		return false;
	if (Changes1.Modifyed_Walls.size() != Changes2.Modifyed_Walls.size())
		return false;
	if (Changes1.New_Walls.size() != Changes2.New_Walls.size())
		return false;
	if (Changes1.Placed_Bomb.size() != Changes2.Placed_Bomb.size())
		return false;
	if (Changes1.Placed_Rocket.size() != Changes2.Placed_Rocket.size())
		return false;
	if (Changes1.Placed_Bonuses.size() != Changes2.Placed_Bonuses.size())
		return false;
	if (Changes1.Collected_Bonuses.size() != Changes2.Collected_Bonuses.size())
		return false;

	for (size_t i = 0; i < Changes1.Killed_Players.size(); i++) {
		if (Changes1.Killed_Players[i] != Changes2.Killed_Players[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.Exploded_Bombs.size(); i++) {
		if (Changes1.Exploded_Bombs[i] != Changes2.Exploded_Bombs[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.Exploded_Rockets.size(); i++) {
		if (Changes1.Exploded_Rockets[i] != Changes2.Exploded_Rockets[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.Modifyed_Walls.size(); i++) {
		if (Changes1.Modifyed_Walls[i] != Changes2.Modifyed_Walls[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.New_Walls.size(); i++) {
		if (Changes1.New_Walls[i] != Changes2.New_Walls[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.Placed_Bomb.size(); i++) {
		if (Changes1.Placed_Bomb[i] != Changes2.Placed_Bomb[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.Placed_Rocket.size(); i++) {
		if (Changes1.Placed_Rocket[i] != Changes2.Placed_Rocket[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.Placed_Bonuses.size(); i++) {
		if (Changes1.Placed_Bonuses[i] != Changes2.Placed_Bonuses[i])
			return false;
	}

	for (size_t i = 0; i < Changes1.Collected_Bonuses.size(); i++) {
		if (Changes1.Collected_Bonuses[i] != Changes2.Collected_Bonuses[i])
			return false;
	}
	
	return true;
}

bool operator != (const Changes &Changes1, const Changes &Changes2){
	return (!(Changes1 == Changes2));
}

Changes operator + ( const Changes &Changes1, const Changes &Changes2) {
	Changes ans;
	
	ans.Exploded_Bombs.reserve(Changes1.Exploded_Bombs.size() + Changes2.Exploded_Bombs.size());
	for (size_t i = 0; i < Changes1.Exploded_Bombs.size(); i++)
		ans.Exploded_Bombs.push_back(Changes1.Exploded_Bombs[i]);
	for (size_t i = 0; i < Changes2.Exploded_Bombs.size(); i++)
		ans.Exploded_Bombs.push_back(Changes2.Exploded_Bombs[i]);
	
	ans.Exploded_Rockets.reserve(Changes1.Exploded_Rockets.size() + Changes2.Exploded_Rockets.size());
	for (size_t i = 0; i < Changes1.Exploded_Rockets.size(); i++)
		ans.Exploded_Rockets.push_back(Changes1.Exploded_Rockets[i]);
	for (size_t i = 0; i < Changes2.Exploded_Rockets.size(); i++)
		ans.Exploded_Rockets.push_back(Changes2.Exploded_Rockets[i]);
	
	ans.Killed_Players.reserve(Changes1.Killed_Players.size() + Changes2.Killed_Players.size());
	for (size_t i = 0; i < Changes1.Killed_Players.size(); i++)
		ans.Killed_Players.push_back(Changes1.Killed_Players[i]);
	for (size_t i = 0; i < Changes2.Killed_Players.size(); i++)
		ans.Killed_Players.push_back(Changes2.Killed_Players[i]);
	
	ans.Modifyed_Walls.reserve(Changes1.Modifyed_Walls.size() + Changes2.Modifyed_Walls.size());
	for (size_t i = 0; i < Changes1.Modifyed_Walls.size(); i++)
		ans.Modifyed_Walls.push_back(Changes1.Modifyed_Walls[i]);
	for (size_t i = 0; i < Changes2.Modifyed_Walls.size(); i++)
		ans.Modifyed_Walls.push_back(Changes2.Modifyed_Walls[i]);
	
	ans.New_Walls.reserve(Changes1.New_Walls.size() + Changes2.New_Walls.size());
	for (size_t i = 0; i < Changes1.New_Walls.size(); i++)
		ans.New_Walls.push_back(Changes1.New_Walls[i]);
	for (size_t i = 0; i < Changes2.New_Walls.size(); i++)
		ans.New_Walls.push_back(Changes2.New_Walls[i]);
	
	ans.Placed_Bomb.reserve(Changes1.Placed_Bomb.size() + Changes2.Placed_Bomb.size());
	for (size_t i = 0; i < Changes1.Placed_Bomb.size(); i++)
		ans.Placed_Bomb.push_back(Changes1.Placed_Bomb[i]);
	for (size_t i = 0; i < Changes2.Placed_Bomb.size(); i++)
		ans.Placed_Bomb.push_back(Changes2.Placed_Bomb[i]);
	
	ans.Placed_Rocket.reserve(Changes1.Placed_Rocket.size() + Changes2.Placed_Rocket.size());
	for (size_t i = 0; i < Changes1.Placed_Rocket.size(); i++)
		ans.Placed_Rocket.push_back(Changes1.Placed_Rocket[i]);
	for (size_t i = 0; i < Changes2.Placed_Rocket.size(); i++)
		ans.Placed_Rocket.push_back(Changes2.Placed_Rocket[i]); 
	
	ans.Placed_Bonuses.reserve(Changes1.Placed_Bonuses.size() + Changes2.Placed_Bonuses.size());
	for (size_t i = 0; i < Changes1.Placed_Bonuses.size(); i++)
		ans.Placed_Bonuses.push_back(Changes1.Placed_Bonuses[i]);
	for (size_t i = 0; i < Changes2.Placed_Bonuses.size(); i++)
		ans.Placed_Bonuses.push_back(Changes2.Placed_Bonuses[i]);

	ans.Collected_Bonuses.reserve(Changes1.Collected_Bonuses.size() + Changes2.Collected_Bonuses.size());
	for (size_t i = 0; i < Changes1.Collected_Bonuses.size(); i++)
		ans.Collected_Bonuses.push_back(Changes1.Collected_Bonuses[i]);
	for (size_t i = 0; i < Changes2.Collected_Bonuses.size(); i++)
		ans.Collected_Bonuses.push_back(Changes2.Collected_Bonuses[i]);
	return ans;
}

Changes operator += (Changes &Changes1, const Changes &Changes2) {
	Changes ans = Changes1 + Changes2;
	Changes1 = ans;
	return ans;
}

void Clear(Changes &Changes1) {
	Changes1.Exploded_Bombs.clear();
	Changes1.Exploded_Rockets.clear();
	Changes1.Killed_Players.clear();
	Changes1.Modifyed_Walls.clear();
	Changes1.New_Walls.clear();
	Changes1.Placed_Bomb.clear();
	Changes1.Placed_Rocket.clear();
	Changes1.Placed_Bonuses.clear();
	Changes1.Collected_Bonuses.clear();
	return;
}