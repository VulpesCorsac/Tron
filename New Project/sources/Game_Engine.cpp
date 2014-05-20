#include "stdafx.h"
#include "headers\Game_Engine.h"

int Game_Engine::round(const double &x) const {
	return (int)floor(x + 0.5);
}

Polygon2D < double > Game_Engine::Polygon_from(const Point2D < double > &C_p, const Vector2D < double > &V, const double &w) {
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

// INTERSECTIONS
bool Game_Engine::Intersect(const LightCycle &Cycle, const Wall &_Wall) {
	return Cross_polygon(Polygon_from_cycle(Cycle), Polygon_from_wall(_Wall));
}

bool Game_Engine::Intersect(const LightCycle &Cycle1, const LightCycle &Cycle2) {
	return Cross_polygon(Polygon_from_cycle(Cycle1), Polygon_from_cycle(Cycle2));
}

bool Game_Engine::Intersect(const LightCycle &Cycle, const Bomb &_Bomb) {
	Polygon2D < double > Poly = Polygon_from_cycle(Cycle);
	Circle < double > Circ(_Bomb.Current_Point, _Bomb.Radius);
	return (Cross_polygon_circle(Poly, Circ) || Polygon_in_circle(Poly, Circ));
}

bool Game_Engine::Intersect(const LightCycle &Cycle, const Rocket &_Rocket) {
	Polygon2D < double > Poly = Polygon_from_cycle(Cycle);
	Circle < double > Circ(_Rocket.Current_Point, _Rocket.Radius);
	return (Cross_polygon_circle(Poly, Circ) || Polygon_in_circle(Poly, Circ));
}

bool Game_Engine::Intersect(const Player &_Player, const Bomb &_Bomb) {
	return Intersect(_Player.MyCycle, _Bomb);
}

bool Game_Engine::Intersect(const Player &_Player, const Rocket &_Rocket) {
	return Intersect(_Player.MyCycle, _Rocket);
}

bool Game_Engine::Intersect(const Player &_Player1, const Player &_Player2) {
	return Intersect(_Player1.MyCycle, _Player2.MyCycle);
}

bool Game_Engine::Intersect(const Wall &_Wall, const Bomb &_Bomb) {
	Point2D < double > P1, P2;
	Circle < double > Circ(_Bomb.Current_Point, _Bomb.Radius);
	return(Cross_segment_circle(_Wall.Segment, Circ, P1, P2));
}

bool Game_Engine::Intersect(const Wall &_Wall, const Rocket &_Rocket) {
	Point2D < double > P1, P2;
	Circle < double > Circ(_Rocket.Current_Point, _Rocket.Radius);
	return(Cross_segment_circle(_Wall.Segment, Circ, P1, P2));
}

bool Game_Engine::Intersect(const Player &_Player, const Bonus &_Bonus, const double &dt) {
	LightCycle _Cycle = _Player.MyCycle;
	Point2D < double > P1 = Polygon_from_cycle(_Cycle).Polygon[0];
	Point2D < double > P2 = Polygon_from_cycle(_Cycle).Polygon[1];
	_Cycle.UPD(dt);
	Point2D < double > P3 = Polygon_from_cycle(_Cycle).Polygon[2];
	Point2D < double > P4 = Polygon_from_cycle(_Cycle).Polygon[3];
	Point2D < double > O = _Bonus.Point;
	if (P4.x == P1.x)
	if (O.x < max(P1.x, P2.x) &&
		O.x > min(P1.x, P2.x) &&
		O.y < max(P1.y, P4.y) &&
		O.y > min(P1.y, P4.y))
		return true;
	if (P4.x == P3.x)
	if (O.x < max(P3.x, P2.x) &&
		O.x > min(P3.x, P2.x) &&
		O.y < max(P3.y, P4.y) &&
		O.y > min(P3.y, P4.y))
		return true;
	if ((P4.y > P1.y) && (P4.y > P3.y))
	if ((O.y > P2.y + (O.x - P2.x)*(P1.y - P2.y) / (P1.x - P2.x)) &&
		(O.y > P2.y + (O.x - P2.x)*(P3.y - P2.y) / (P3.x - P2.x)) &&
		(O.y < P4.y + (O.x - P4.x)*(P3.y - P4.y) / (P3.x - P4.x)) &&
		(O.y < P4.y + (O.x - P4.x)*(P1.y - P4.y) / (P1.x - P4.x)))
		return true;
	if ((P2.y > P1.y) && (P2.y > P3.y))
	if ((O.y < P2.y + (O.x - P2.x)*(P1.y - P2.y) / (P1.x - P2.x)) &&
		(O.y < P2.y + (O.x - P2.x)*(P3.y - P2.y) / (P3.x - P2.x)) &&
		(O.y > P4.y + (O.x - P4.x)*(P3.y - P4.y) / (P3.x - P4.x)) &&
		(O.y > P4.y + (O.x - P4.x)*(P1.y - P4.y) / (P1.x - P4.x)))
		return true;
	if ((P1.y > P2.y) && (P1.y > P4.y))
	if ((O.y < P2.y + (O.x - P2.x)*(P1.y - P2.y) / (P1.x - P2.x)) &&
		(O.y > P2.y + (O.x - P2.x)*(P3.y - P2.y) / (P3.x - P2.x)) &&
		(O.y > P4.y + (O.x - P4.x)*(P3.y - P4.y) / (P3.x - P4.x)) &&
		(O.y < P4.y + (O.x - P4.x)*(P1.y - P4.y) / (P1.x - P4.x)))
		return true;
	if ((P3.y > P1.y) && (P3.y > P2.y))
	if ((O.y > P2.y + (O.x - P2.x)*(P1.y - P2.y) / (P1.x - P2.x)) &&
		(O.y < P2.y + (O.x - P2.x)*(P3.y - P2.y) / (P3.x - P2.x)) &&
		(O.y < P4.y + (O.x - P4.x)*(P3.y - P4.y) / (P3.x - P4.x)) &&
		(O.y > P4.y + (O.x - P4.x)*(P1.y - P4.y) / (P1.x - P4.x)))
		return true;
	return false;
}

// BOMBS
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
	assert(n >= 0 && n < (int)this->Current_Game.Bombs.size() && "Trying to delete bomb that does not exist");
	this->Current_Game.Bombs.erase(this->Current_Game.Bombs.begin() + n);
	return true;
}

bool Game_Engine::Bomb_Delete(const Bomb &_Bomb) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Bombs.size(); i++)
	if (_Bomb == this->Current_Game.Bombs[i]) {
		Bomb_Delete((int)i);
		return true;
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

void Game_Engine::Bomb_Explosion(const int &Bomb_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls) {
	assert(Bomb_Number >= 0 && Bomb_Number < (int)this->Current_Game.Bombs.size() && "Trying to explode bomb that does not exist");
	Circle < double > C(this->Current_Game.Bombs[Bomb_Number].Current_Point, this->Current_Game.Bombs[Bomb_Number].Radius);
	Make_some_magic(C, Killed_Players, New_Tails, Deleted_Walls, New_walls);
	return;
}

// ROCKETS
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
	assert(n >= 0 && n < (int)this->Current_Game.Rockets.size() && "Trying to delete rocket that does not exist");
	this->Current_Game.Rockets.erase(this->Current_Game.Rockets.begin() + n);
	return true;
}

bool Game_Engine::Rocket_Delete(const Rocket &_Rocket) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Rockets.size(); i++)
	if (_Rocket == this->Current_Game.Rockets[i]) {
		f = Rocket_Delete((int)i);
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

void Game_Engine::Rocket_Explosion(const int &Rocket_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls) {
	assert(Rocket_Number >= 0 && Rocket_Number < (int)this->Current_Game.Rockets.size() && "Trying to explode rocket that does not exist");
	Circle < double > C(this->Current_Game.Rockets[Rocket_Number].Current_Point, this->Current_Game.Rockets[Rocket_Number].Radius);
	Make_some_magic(C, Killed_Players, New_Tails, Deleted_Walls, New_walls);
	return;
}

// WALLS
void Game_Engine::Wall_Add(const Wall &_Wall) {
	this->Current_Game.Walls.push_back(_Wall);
	return;
}

void Game_Engine::Wall_Add(const vector < Wall > &Walls) {
	for (size_t i = 0; i < Walls.size(); i++)
		Wall_Add(Walls[i]);
	return;
}

bool Game_Engine::Wall_Modify(const int &n, const Wall &New_Wall) {
	assert(n >= 0 && n <= (int)this->Current_Game.Walls.size() && "Trying to modify wall that does not exist");
	this->Current_Game.Walls[n] = New_Wall;
	return true;
}

bool Game_Engine::Wall_Modify(const Wall &_Wall, const Wall &New_Wall) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++)
	if (_Wall == this->Current_Game.Walls[i]) {
		f = Wall_Modify((int)i, New_Wall);
		break;
	}
	return f;
}

bool Game_Engine::Wall_Modify(const vector < Wall > &Walls, const vector < Wall > &New_Walls) {
	if (Walls.size() != New_Walls.size()) {
		cerr << "Error! Walls ans New_Walls have different sizes" << endl;
		throw - 1;
	}
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++)
	if (Wall_Modify(Walls[i], New_Walls[i]))
		f = true;
	return f;
}

bool Game_Engine::Wall_Delete(const int &n) {
	assert(n >= 0 && n < (int)this->Current_Game.Walls.size() && "Trying to delete wall that does not exist");
	this->Current_Game.Walls.erase(this->Current_Game.Walls.begin() + n);
	return true;
}

bool Game_Engine::Wall_Delete(const Wall &_Wall) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++)
	if (_Wall == this->Current_Game.Walls[i]) {
		f = Wall_Delete((int)i);
		break;
	}
	return f;
}

bool Game_Engine::Wall_Delete(const vector < Wall > &Walls) {
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++)
	if (Wall_Delete(Walls[i]))
		f = true;
	return f;
}

bool Game_Engine::Wall_Delete_flag(const int &n) {
	assert(n >= 0 && n < (int)this->Current_Game.Walls.size() && "Trying to delete wall that does not exist");
	return Wall_Modify(n, Wall(Segment2D < double >(Point2D < double >(-1, -1), Point2D < double >(-1, -1)), -1));
	this->Current_Game.Walls.erase(this->Current_Game.Walls.begin() + n);
	return true;
}

bool Game_Engine::Wall_Delete_flag(const Wall &_Wall) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++)
	if (_Wall == this->Current_Game.Walls[i]) {
		f = Wall_Delete_flag((int)i);
		break;
	}
	return f;
}

bool Game_Engine::Wall_Delete_flag(const vector < Wall > &Walls) {
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++)
	if (Wall_Delete_flag(Walls[i]))
		f = true;
	return f;
}

// BONUSES
void Game_Engine::Bonus_Add(const Bonus &_Bonus) {
	this->Current_Game.Bonuses.push_back(_Bonus);
	return;
}

void Game_Engine::Bonus_Add(const vector < Bonus > &Bonuses) {
	for (size_t i = 0; i < Bonuses.size(); i++)
		Bonus_Add(Bonuses[i]);
	return;
}

bool Game_Engine::Bonus_Delete(const int &n) {
	assert(n >= 0 && n <= (int)this->Current_Game.Bonuses.size() && "Trying to delete bonus that does not exist");
	this->Current_Game.Bonuses.erase(this->Current_Game.Bonuses.begin() + n);
	return true;
}

bool Game_Engine::Bonus_Delete(const Bonus &_Bonus) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Bonuses.size(); i++)
	if (_Bonus == this->Current_Game.Bonuses[i]) {
		f = Bonus_Delete((int)i);
		break;
	}
	return f;
}

bool Game_Engine::Bonus_Delete(const vector < Bonus > &Bonuses) {
	bool f = false;
	for (size_t i = 0; i < Bonuses.size(); i++)
	if (Bonus_Delete(Bonuses[i]))
		f = true;
	return f;
}

// PLAYERS
Player Game_Engine::Player_Generate(void) {
	double x, y;
	int Width = round(this->Constants->Field_Width);
	int Length = round(this->Constants->Field_Length);
	x = (double)(rand() % Width);
	y = (double)(rand() % Length);
	Point2D < double > Point(x, y);

	int dir = rand() % 4;
	switch (dir) {
	case 0: x = 1; y = 0; break;
	case 1: x = 0; y = 1; break;
	case 2: x = -1; y = 0; break;
	case 3: x = 0; y = -1; break;
	default: x = 0; y = 0; break;
	}
	Vector2D < double > Direction(x, y);

	Player Temp(Point, Direction, this->Constants);
	return Temp;
}

vector < Player > Game_Engine::Player_Generate(const int &n) {
	vector < Player > Temp(n);
	for (int i = 0; i < n; i++)
		Temp[i] = Player_Generate();
	return Temp;
}

void Game_Engine::PLayer_Kill(const int &Player_number) {
	assert(Player_number <= this->Current_Game.Players_Ammount && "Player you are trying to kill has a greater number, than it can be");
	assert(Player_number >= 0 && "You are trying to kill a player with a negative number");
	int killed = 0;
	if (this->Current_Game.Players[Player_number].Player_Number == Player_number) {
		if (!this->Current_Game.Players[Player_number].Alive)
			killed = 2;
		else
			killed = 1;
		this->Current_Game.Players[Player_number].Kill();
	} else {
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
			Wall_Delete_flag((int)i);
	return;
}

void Game_Engine::Player_Add(Player &_Player) {
	this->Current_Game.Players_Ammount++;
	_Player.Player_Number = this->Current_Game.Players_Ammount;
	this->Current_Game.Players.push_back(_Player);
	return;
}

void Game_Engine::Player_Add(vector < Player > &Players) {
	for (size_t i = 0; i < Players.size(); i++)
		Player_Add(Players[i]);
	return;
}
