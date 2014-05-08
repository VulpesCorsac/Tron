#include "stdafx.h"
#include "headers\Game.h"

void Game::Kill_PLayer(const int &Player_number) {
	assert(Player_number <= this->Players_Ammount && "Player you are trying to kill has a greater number, than it can be");
	assert(Player_number >= 0 && "You are trying to kill a player with a negative number");
	int killed = 0;
	if (this->Players[Player_number].Player_Number == Player_number) {
		if (!this->Players[Player_number].Alive)
			killed = 2;
		else
			killed = 1;
		this->Players[Player_number].Kill();
	} else {
		for (int i = 0; i < this->Players_Ammount; i++)
			if (this->Players[i].Player_Number == Player_number) {
				if (!this->Players[i].Alive)
					killed = 2;
				else
					killed = 1;
				this->Players[i].Kill();
				break;
			}
	}
	if (killed == 0) {
		cerr << "Trying to kill a Player, that is not in Players range" << endl;
		throw -1;
	}
	if (killed == 2) {
		cerr << "Trying to kill a Player, that is already dead" << endl;
		throw -1;
	}

	for (size_t i = 0; i < this->Walls.size(); i++)
		if (this->Walls[i].PlayerNumber == Player_number)
			this->Walls[i].PlayerNumber = -1;
	return;
}