#include "stdafx.h"
#include "headers\Game_Engine.h"

Polygon2D < double > Game_Engine::Polygon_from(const Point2D < double > &C_p, const Vector2D < double > &V, const double w) {
	vector < Point2D < double > > Pol;
	if (V.y == 0) {
		Pol.push_back(Point2D < double >(C_p.x - w / 2.0, C_p.y));
		Pol.push_back(Point2D < double >(C_p.x + w / 2.0, C_p.y));
		Pol.push_back(Pol[0] + V);
		Pol.push_back(Pol[1] + V);
	}
	else {
		Pol.push_back(Point2D < double >(C_p.x + w / (2.0*SQRT(1 + SQR(V.x / V.y))), 0));
		Pol[0].y = C_p.y - V.x*(Pol[0].x - C_p.x) / V.y;
		Pol.push_back(Point2D < double >(C_p.x - w / (2.0*SQRT(1 + SQR(V.x / V.y))), 0));
		Pol[1].y = C_p.y - V.x*(Pol[1].x - C_p.x) / V.y;
		Pol.push_back(Pol[1] + V);
		Pol.push_back(Pol[0] + V);
	}
	return Polygon2D < double >(Pol);
}

Polygon2D < double > Game_Engine::Polygon_from_cycle(const LightCycle &Cycle) {
	return Polygon_from(Cycle.Current_Point, this->Constants->LightCycle_Length * Norm(Cycle.Direction), this->Constants->LightCycle_Width);
}

Polygon2D < double > Game_Engine::Polygon_from_wall(const Wall &_Wall) {
	return Polygon_from(_Wall.Segment.A, Vector2D < double >(_Wall.Segment.A, _Wall.Segment.B), this->Constants->Wall_Width);
}

bool Game_Engine::Intersect(const LightCycle &Cycle, const Wall &_Wall) {
	return Cross_polygon(Polygon_from_cycle(Cycle), Polygon_from_wall(_Wall));
}

bool Game_Engine::Intersect(const LightCycle &Cycle1, const LightCycle &Cycle2) {
	return Cross_polygon(Polygon_from_cycle(Cycle1), Polygon_from_cycle(Cycle2));
}

void Game_Engine::Bomb_Add(const Bomb &_Bomb) {
	this->Current_Game.Bombs.push_back(_Bomb);
	return;
}

void Game_Engine::Bomb_Add(const vector < Bomb > &Bombs) {
	for (size_t i = 0; i < Bombs.size(); i++)
		Bomb_Add(Bombs[i]);
	return;
}

bool Game_Engine::Bomb_Delete(const int &n) {
	if (n >= this->Current_Game.Bombs.size()) {
		cerr << "Trying to delete bomb that does not exist" << endl;
		throw - 1;
	}
	this->Current_Game.Bombs.erase(this->Current_Game.Bombs.begin() + n);
	return true;
}

bool Game_Engine::Bomb_Delete(const Bomb &_Bomb) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Bombs.size(); i++)
		if (_Bomb == this->Current_Game.Bombs[i]) {
			f = Bomb_Delete((int) i);
			break;
		}
	return f;
}

bool Game_Engine::Bomb_Delete(const vector < Bomb > &Bombs) {
	bool f = false;
	for (size_t i = 0; i < Bombs.size(); i++)
		if (Bomb_Delete(Bombs[i]))
			f = true;
		return f;
}

void Game_Engine::Rocket_Add(const Rocket &_Rocket) {
	this->Current_Game.Rockets.push_back(_Rocket);
	return;
}

void Game_Engine::Rocket_Add(const vector < Rocket > &Rockets) {
	for (size_t i = 0; i < Rockets.size(); i++)
		Rocket_Add(Rockets[i]);
	return;
}

bool Game_Engine::Rocket_Delete(const int &n) {
	if (n >= this->Current_Game.Rockets.size()) {
		cerr << "Trying to delete rocket that does not exist" << endl;
		throw - 1;
	}
	this->Current_Game.Rockets.erase(this->Current_Game.Rockets.begin() + n);
	return true;
}

bool Game_Engine::Rocket_Delete(const Rocket &_Rocket) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Rockets.size(); i++)
	if (_Rocket == this->Current_Game.Rockets[i]) {
		f = Rocket_Delete((int) i);
		break;
	}
	return f;
}

bool Game_Engine::Rocket_Delete(const vector < Rocket > &Rockets) {
	bool f = false;
	for (size_t i = 0; i < Rockets.size(); i++)
	if (Rocket_Delete(Rockets[i]))
		f = true;
	return f;
}

void Game_Engine::Kill_PLayer(const int &Player_number) {
	assert(Player_number <= this->Current_Game.Players_Ammount && "Player you are trying to kill has a greater number, than it can be");
	assert(Player_number >= 0 && "You are trying to kill a player with a negative number");
	int killed = 0;
	if (this->Current_Game.Players[Player_number].Player_Number == Player_number) {
		if (!this->Current_Game.Players[Player_number].Alive)
			killed = 2;
		else
			killed = 1;
		this->Current_Game.Players[Player_number].Kill();
	}
	else {
		for (int i = 0; i < this->Current_Game.Players_Ammount; i++)
		if (this->Current_Game.Players[i].Player_Number == Player_number) {
			if (!this->Current_Game.Players[i].Alive)
				killed = 2;
			else
				killed = 1;
			this->Current_Game.Players[i].Kill();
			break;
		}
	}
	if (killed == 0) {
		cerr << "Trying to kill a Player, that is not in Players range" << endl;
		throw - 1;
	}
	if (killed == 2) {
		cerr << "Trying to kill a Player, that is already dead" << endl;
		throw - 1;
	}

	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++)
	if (this->Current_Game.Walls[i].PlayerNumber == Player_number)
		this->Current_Game.Walls[i].PlayerNumber = -1;
	return;
}