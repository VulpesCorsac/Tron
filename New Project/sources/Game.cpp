#include "stdafx.h"
#include "headers\Game.h"

void Game::Clear(void) {
	this->Bombs.clear();
	this->Bonuses.clear();
	this->Players.clear();
	this->Players_Ammount = 0;
	this->Rockets.clear();
	this->Walls.clear();
	return;
}

void Game::Start(const vector < Player > &_Players) {
	Clear();
	this->Players_Ammount = _Players.size();
	this->Players = _Players;
	this->Walls.resize(this->Players_Ammount);
	for (size_t i = 0; i < this->Walls.size(); i++) {
		this->Walls[i] = Wall(Segment2D < double >(this->Players[i].MyCycle.Current_Point, this->Players[i].MyCycle.Current_Point), (int)i, (int)i);
	}
}
