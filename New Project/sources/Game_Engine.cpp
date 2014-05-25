#include "stdafx.h"
#include "headers\Game_Engine.h"

bool WallComparator(Wall &Wall1, Wall &Wall2) {
	if (Wall1.Wall_Number != -1 && Wall2.Wall_Number != -1)
		return (Wall1.Wall_Number < Wall2.Wall_Number);
	if (Wall1.Wall_Number != -1 && Wall2.Wall_Number == -1)
		return true;
	if (Wall1.Wall_Number == -1 && Wall2.Wall_Number != -1)
		return false;
	return true;
}

void Game_Engine::WallSort(const int &n1, const int &n2) {
	sort(this->Current_Game.Walls.begin() + n1, this->Current_Game.Walls.begin() + n2 + 1, WallComparator);
	for (size_t i = this->Veryfied_Walls; i < this->Current_Game.Walls.size(); i++) {
		if (this->Current_Game.Walls[i].Wall_Number == -1) {
			this->Veryfied_Walls = i - 1;
			return;
		}
	}
	return;
}

void Game_Engine::WallSort(const int &n1) {
	WallSort(n1, this->Current_Game.Walls.size());
	return;
}

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
	} else {
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

bool Game_Engine::Intersect(const Polygon2D < double > &P1, const Polygon2D < double > &P2) {
	return Cross_polygon(P1, P2);
}

int Game_Engine::Intersect_Tails(const Player &_Player1, const Player &_Player2, const double &dt) {
	vector < Point2D < double > > V_1,V_2;
	V_1.clear();
	V_2.clear();
	Polygon2D <double> P;
	LightCycle _Cycle = _Player1.MyCycle;
	P = Polygon_from_cycle(_Cycle);
	V_1.push_back(P.Polygon[0]);
	V_1.push_back(P.Polygon[1]);
	_Cycle.UPD(dt);
	P = Polygon_from_cycle(_Cycle);
	V_1.push_back(P.Polygon[2]);
	V_1.push_back(P.Polygon[3]);
	Polygon2D < double > Pol1(V_1);

	_Cycle = _Player2.MyCycle;
	P = Polygon_from_cycle(_Cycle);
	V_2.push_back(P.Polygon[0]);
	V_2.push_back(P.Polygon[1]);
	_Cycle.UPD(dt);
	P = Polygon_from_cycle(_Cycle);
	V_2.push_back(P.Polygon[2]);
	V_2.push_back(P.Polygon[3]);
	Polygon2D < double > Pol2(V_2);

	if (Intersect(Pol1, Pol2)) {
		Line2D < double > L1(0.5*(V_1[1] + V_1[0]), 0.5*(V_1[2] + V_1[3]));
		Line2D < double > L2(0.5*(V_2[1] + V_2[0]), 0.5*(V_2[2] + V_2[3]));
		Point2D < double > Cross_P;
		double dist1, dist2;
		Cross_line(L1, L2, Cross_P);
		if (abs(dist(Cross_P, 0.5*(V_1[1] + V_1[0])) + this->Constants->LightCycle_Length - dist(Cross_P, 0.5*(V_1[2] + V_1[3]))) < EPS)
			dist1 = -dist(Cross_P, 0.5*(V_1[1] + V_1[0]));
		else
			dist1 = dist(Cross_P, 0.5*(V_1[1] + V_1[0]));
		if (abs(dist(Cross_P, 0.5*(V_2[1] + V_2[0])) + this->Constants->LightCycle_Length - dist(Cross_P, 0.5*(V_2[2] + V_2[3]))) < EPS)
			dist2 = -dist(Cross_P, 0.5*(V_2[1] + V_2[0]));
		else
			dist2 = dist(Cross_P, 0.5*(V_2[1] + V_2[0]));
		if (dist1 + 1.5*this->Constants->LightCycle_Length < dist2)
			return 1;
		if (dist2 + 1.5*this->Constants->LightCycle_Length < dist1)
			return 2;
		return 3;
	}
	return 0;
}

bool Game_Engine::Intersect_Walls_Not_Tails(const Player &_Player, const double &dt) {
	vector < Point2D < double > > V_1;
	V_1.clear();

	LightCycle _Cycle = _Player.MyCycle;
	V_1.push_back(Polygon_from_cycle(_Cycle).Polygon[0]);
	V_1.push_back(Polygon_from_cycle(_Cycle).Polygon[1]);
	_Cycle.UPD(dt);
	V_1.push_back(Polygon_from_cycle(_Cycle).Polygon[2]);
	V_1.push_back(Polygon_from_cycle(_Cycle).Polygon[3]);
	Polygon2D < double > Pol1(V_1);

	for (size_t i = this->Current_Game.Players.size(); i < this->Current_Game.Walls.size(); i++) {
		Polygon2D < double > Pol2 = Polygon_from_wall(this->Current_Game.Walls[i]);
		if (Intersect(Pol1, Pol2))
			return true;
	}
	return false;
}

void Game_Engine::Make_some_magic(const Circle < double > &C, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls) {
	Killed_Players.clear();
	New_Tails.clear();
	Deleted_Walls.clear();
	New_walls.clear();
	Point2D < double > P1, P2, Player_Point;
	for (size_t i = 0; i < this->Current_Game.Players.size(); i++) {
		if (Cross_polygon_circle(Polygon_from_cycle(this->Current_Game.Players[i].MyCycle), C))
			Killed_Players.push_back(this->Current_Game.Players[i].Player_Number);
		else {
			Player_Point = this->Current_Game.Players[i].MyCycle.Current_Point;
			if (Cross_segment_circle(this->Current_Game.Walls[i].Segment, C, P1, P2) == 2) {
				Deleted_Walls.push_back(i);
				if (dist(P1, Player_Point) <= dist(P2, Player_Point)) {
					New_Tails.push_back(std::make_pair(i, Wall(Segment2D <double>(Player_Point, P1), i, i)));
					if (Player_Point == this->Current_Game.Walls[i].Segment.B)
						New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.A, P2), i));
					else
						New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.B, P2), i));
				} else {
					New_Tails.push_back(std::make_pair(i, Wall(Segment2D <double>(Player_Point, P2), i, i)));
					if (Player_Point == this->Current_Game.Walls[i].Segment.B)
						New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.A, P1), i));
					else
						New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.B, P1), i));
				}
			}
			if (Cross_segment_circle(this->Current_Game.Walls[i].Segment, C, P1, P2) == 1) {
				Deleted_Walls.push_back(i);
				if (dist(P1, Player_Point) <= dist(P2, Player_Point))
					New_Tails.push_back(std::make_pair(i, Wall(Segment2D <double>(Player_Point, P1), i, i)));
				else
					New_Tails.push_back(std::make_pair(i, Wall(Segment2D <double>(Player_Point, P2), i, i)));
			}
		}
	}

	for (size_t i = this->Current_Game.Players.size(); i < this->Current_Game.Walls.size(); i++) {
		if (Cross_segment_circle(this->Current_Game.Walls[i].Segment, C, P1, P2) == 2) {
			Deleted_Walls.push_back(i);
			if (dist(P1, this->Current_Game.Walls[i].Segment.A) <= dist(P2, this->Current_Game.Walls[i].Segment.A)) {
				New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.A, P1), i));
				New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.B, P2), i));
			} else {
				New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.B, P1), i));
				New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.A, P2), i));
			}
		}
		if (Cross_segment_circle(this->Current_Game.Walls[i].Segment, C, P1, P2) == 1) {
			Deleted_Walls.push_back(i);
			if (Point_in_circle(this->Current_Game.Walls[i].Segment.A, C))
				New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.A, P1), i));
			else
				New_walls.push_back(Wall(Segment2D <double>(this->Current_Game.Walls[i].Segment.B, P1), i));
		}
		if (Point_in_circle(this->Current_Game.Walls[i].Segment.A, C))
			Deleted_Walls.push_back(i);
	}
	return;
}

bool Game_Engine::Out_of_Field(const Player &_Player, const double &dt) {
	LightCycle _Cycle = _Player.MyCycle;
	_Cycle.UPD(dt);
	Point2D < double > P = _Cycle.Current_Point + this->Constants->LightCycle_Length*Norm(_Cycle.Direction);
	if ((P.x < 0) || (P.x > this->Constants->Field_Width) || (P.y < 0) || (P.y > this->Constants->LightCycle_Length))
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
	for (size_t i = 0; i < this->Current_Game.Bombs.size(); i++) {
		if (_Bomb == this->Current_Game.Bombs[i])
			return Bomb_Delete((int)i);
	}
	return false;
}

bool Game_Engine::Bomb_Delete(const vector < int > &Bombs) {
	bool f = false;
	for (size_t i = 0; i < Bombs.size(); i++) {
		if (Bomb_Delete(Bombs[i]))
			f = true;
	}
	return f;
}

bool Game_Engine::Bomb_Delete(const vector < Bomb > &Bombs) {
	bool f = false;
	for (size_t i = 0; i < Bombs.size(); i++) {
		if (Bomb_Delete(Bombs[i]))
			f = true;
	}
	return f;
}

void Game_Engine::Bomb_Explosion(const int &Bomb_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls) {
	assert(Bomb_Number >= 0 && Bomb_Number < (int)this->Current_Game.Bombs.size() && "Trying to explode bomb that does not exist");
	Circle < double > C(this->Current_Game.Bombs[Bomb_Number].Current_Point, this->Current_Game.Bombs[Bomb_Number].Radius);
	Make_some_magic(C, Killed_Players, New_Tails, Deleted_Walls, New_walls);
	return;
}

void Game_Engine::Bomb_Place(const int &Player_number) {
	Bomb _Bomb(this->Current_Game.Players[Player_number].MyCycle.Current_Point, this->Constants->Bomb_Time, this->Constants->Bomb_Radius);
	this->Current_Game.Bombs.push_back(_Bomb);
	this->Game_Changes.Placed_Bomb.push_back(_Bomb);
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
	for (size_t i = 0; i < this->Current_Game.Rockets.size(); i++) {
		if (_Rocket == this->Current_Game.Rockets[i])
			return Rocket_Delete((int)i);
	}
	return false;
}

bool Game_Engine::Rocket_Delete(const vector < int > &Rockets) {
	bool f = false;
	for (size_t i = 0; i < Rockets.size(); i++) {
		if (Rocket_Delete(Rockets[i]))
			f = true;
	}
	return f;
}

bool Game_Engine::Rocket_Delete(const vector < Rocket > &Rockets) {
	bool f = false;
	for (size_t i = 0; i < Rockets.size(); i++) {
		if (Rocket_Delete(Rockets[i]))
			f = true;
	}
	return f;
}

void Game_Engine::Rocket_Explosion(const int &Rocket_Number, vector < int > &Killed_Players, vector < std::pair < int, Wall > > &New_Tails, vector < int > &Deleted_Walls, vector < Wall > &New_walls) {
	assert(Rocket_Number >= 0 && Rocket_Number < (int)this->Current_Game.Rockets.size() && "Trying to explode rocket that does not exist");
	Circle < double > C(this->Current_Game.Rockets[Rocket_Number].Current_Point, this->Current_Game.Rockets[Rocket_Number].Radius);
	Make_some_magic(C, Killed_Players, New_Tails, Deleted_Walls, New_walls);
	return;
}

void Game_Engine::Rocket_Place(const int &Player_number) {
	Rocket _Rock(this->Current_Game.Players[Player_number].MyCycle.Current_Point, this->Current_Game.Players[Player_number].MyCycle.Direction, this->Constants->Rocket_Speed, this->Constants->Rocket_Length, this->Constants->Rocket_Radius );
	this->Current_Game.Rockets.push_back(_Rock);
	this->Game_Changes.Placed_Rocket.push_back(_Rock);
	return;
}

// WALLS
bool Game_Engine::Wall_Modify(const int &n, const Wall &New_Wall) {
	assert(n >= 0 && n <= (int)this->Current_Game.Walls.size() && "Trying to modify wall that does not exist");
	this->Current_Game.Walls[n] = New_Wall;
	return true;
}

bool Game_Engine::Wall_Modify(const Wall &_Wall, const Wall &New_Wall) {
	if (Equal(this->Current_Game.Walls[_Wall.Wall_Number], _Wall))
		return Wall_Modify((int)_Wall.Wall_Number, New_Wall);
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++) {
		if (Equal(_Wall, this->Current_Game.Walls[i]))
			return Wall_Modify((int)i, New_Wall);
	}
	return false;
}

bool Game_Engine::Wall_Modify(const vector < pair < Wall, Wall > > &Walls) {
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++) {
		if (Wall_Modify(Walls[i].first, Walls[i].second))
			f = true;
	}
	return f;
}

bool Game_Engine::Wall_Prolong(const int &n) {
	assert(n >= 0 && n < this->Current_Game.Players_Ammount && "Trying to prolong tail that does not exist");
	Segment2D < double > Seg(this->Current_Game.Walls[n].Segment.A, this->Current_Game.Players[n].MyCycle.Current_Point);
	return Wall_Modify(n, Wall(Seg, this->Current_Game.Walls[n].Player_Number, this->Current_Game.Walls[n].Wall_Number));
}

bool Game_Engine::Wall_Prolong_All(void) {
	bool f = false;
	for (size_t i = 0; i < this->Current_Game.Players_Ammount; i++) {
		if (this->Current_Game.Players[i].Alive) {
			Wall_Prolong((int)i);
			f = true;
		}
	}
	return f;
}

bool Game_Engine::Wall_Add(const Wall &_Wall) {
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++) {
		if (Equal(_Wall, this->Current_Game.Walls[i]))
			return Wall_Modify((int)i, _Wall);
	}
	this->Current_Game.Walls.push_back(_Wall);
	return false;
}

bool Game_Engine::Wall_Add(const vector < Wall > &Walls) {
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++) {
		if (Wall_Add(Walls[i]))
			f = true;
	}
	return f;
}

bool Game_Engine::Wall_Delete(const int &n) {
	assert(n >= 0 && n < (int)this->Current_Game.Walls.size() && "Trying to delete wall that does not exist");
	this->Current_Game.Walls.erase(this->Current_Game.Walls.begin() + n);
	return true;
}

bool Game_Engine::Wall_Delete(const Wall &_Wall) {
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++) {
		if (Equal(_Wall, this->Current_Game.Walls[i]))
			return Wall_Delete((int)i);
	}
	return false;
}

bool Game_Engine::Wall_Delete(const vector < int > &Walls) {
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++) {
		if (Wall_Delete(Walls[i]))
			f = true;
	}
	return f;
}

bool Game_Engine::Wall_Delete(const vector < Wall > &_Walls) {
	bool f = false;
	for (size_t i = 0; i < _Walls.size(); i++) {
		if (Wall_Delete(_Walls[i]))
			f = true;
	}
	return f;
}

bool Game_Engine::Wall_Delete_flag(const int &n) {
	assert(n >= 0 && n < (int)this->Current_Game.Walls.size() && "Trying to delete wall that does not exist");
	return Wall_Modify(n, Wall(Segment2D < double >(Point2D < double >(-100, -100), Point2D < double >(-100, -100)), this->Current_Game.Walls[n].Player_Number, this->Current_Game.Walls[n].Wall_Number));
}

bool Game_Engine::Wall_Delete_flag(const Wall &_Wall) {
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++) {
		if (Equal(_Wall, this->Current_Game.Walls[i]))
			return Wall_Delete_flag((int)i);
	}
	return false;
}

bool Game_Engine::Wall_Delete_flag(const vector < Wall > &Walls) {
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++) {
		if (Wall_Delete_flag(Walls[i]))
			f = true;
	}
	return f;
}

bool Game_Engine::Wall_Delete_flag(const vector < int > &Walls) {
	bool f = false;
	for (size_t i = 0; i < Walls.size(); i++) {
		if (Wall_Delete_flag(Walls[i]))
			f = true;
	}
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
	for (size_t i = 0; i < this->Current_Game.Bonuses.size(); i++) {
		if (_Bonus == this->Current_Game.Bonuses[i])
			return Bonus_Delete((int)i);
	}
	return false;
}

bool Game_Engine::Bonus_Delete(const vector < int > &Bonuses) {
	bool f = false;
	for (size_t i = 0; i < Bonuses.size(); i++) {
		if (Bonus_Delete(Bonuses[i]))
			f = true;
	}
	return f;
}

bool Game_Engine::Bonus_Delete(const vector < Bonus > &Bonuses) {
	bool f = false;
	for (size_t i = 0; i < Bonuses.size(); i++) {
		if (Bonus_Delete(Bonuses[i]))
			f = true;
	}
	return f;
}

void Game_Engine::Bonus_Place(void) {
	double x, y;
	int Width = round(this->Constants->Field_Width);
	int Length = round(this->Constants->Field_Length);
	x = (double)(rand() % Width);
	y = (double)(rand() % Length);
	Point2D < double > Point(x, y);
	Bonus _Bonus(Point, (int)(rand() % 2));
	this->Current_Game.Bonuses.push_back(_Bonus);
	this->Game_Changes.Placed_Bonuses.push_back(_Bonus);
	return;
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
	for (int i = 0; i < n; i++) {
		Temp[i] = Player_Generate();
		Temp[i].Player_Number = i;
		Temp[i].Team_Number = i; //TODO: for someone
	}
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
	assert(killed == 1 && "Trying to kill a Player, that is not in Players range or trying to kill a Player, that is already dead");
	for (size_t i = 0; i < this->Current_Game.Walls.size(); i++) {
		if (this->Current_Game.Walls[i].Player_Number == Player_number)
			Wall_Delete_flag((int)i);
	}
	return;
}

void Game_Engine::PLayer_Kill(const vector < int > &Players_Numbers) {
	for (size_t i = 0; i < Players_Numbers.size(); i++)
		PLayer_Kill(Players_Numbers[i]);
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

void Game_Engine::Player_Turn(const int &Player_number, const bool &left_turn, State &St, Changes &Ch) {
	Point2D < double >  C_P = this->Current_Game.Players[Player_number].MyCycle.Current_Point;
	Wall N_W(this->Current_Game.Walls[Player_number].Segment, Player_number, this->Current_Game.Walls.size());
	Wall M_W(Segment2D <double>(C_P, C_P), Player_number, Player_number);

	Ch.Modifyed_Walls.push_back(std::make_pair(this->Current_Game.Walls[Player_number], M_W));
	Ch.New_Walls.push_back(N_W);

	this->Current_Game.Players[Player_number].Turn(left_turn);
	this->Current_Game.Walls.push_back(N_W);
	this->Current_Game.Walls[Player_number] = M_W;

	St.Players = this->Current_Game.Players;
}

void Game_Engine::PLayer_Turn_Client(const int &Player_number, const bool &left_turn) {
	Point2D < double >  C_P = this->Current_Game.Players[Player_number].MyCycle.Current_Point;
	this->Current_Game.Players[Player_number].Turn(left_turn);
	this->Current_Game.Walls.push_back(Wall(this->Current_Game.Walls[Player_number].Segment, Player_number, this->Current_Game.Walls.size()));
	this->Current_Game.Walls[Player_number] = Wall(Segment2D <double>(C_P, C_P), Player_number, Player_number);
}

void Game_Engine::_UPD(const double dt, State &St, Changes &Ch) {
	Clear(Ch);
	Clear(St);
	for (size_t i = 0; i < this->Current_Game.Players.size(); i++) {
		if (this->Current_Game.Players[i].Alive) {
			if ((Intersect_Walls_Not_Tails(this->Current_Game.Players[i], dt)) || (Out_of_Field(this->Current_Game.Players[i], dt)))
				Ch.Killed_Players.push_back(i);
			else
			for (size_t j = i; j < this->Current_Game.Players.size() - 1; j++) {
				if (this->Current_Game.Players[j].Alive) {
					if (Intersect_Tails(this->Current_Game.Players[i], this->Current_Game.Players[j + 1], dt) == 3) {
						Ch.Killed_Players.push_back(i);
						Ch.Killed_Players.push_back(j + 1);
						break;
					}
					if (Intersect_Tails(this->Current_Game.Players[i], this->Current_Game.Players[j + 1], dt) == 1) {
						Ch.Killed_Players.push_back(i);
						break;
					}
					if (Intersect_Tails(this->Current_Game.Players[i], this->Current_Game.Players[j + 1], dt) == 2)
						Ch.Killed_Players.push_back(j + 1);
				}
			}
		}
	}

	vector < int > K_Ps;
	vector < std::pair < int, Wall > > N_Ts;
	vector < int > D_Ws;
	vector < Wall > N_Ws;
	Changes Ch_buf;
	for (size_t i = 0; i < this->Current_Game.Bombs.size(); i++) {
		if (this->Current_Game.Bombs[i].Explode()) {
			Clear(Ch_buf);
			Bomb_Explosion(i, Ch_buf.Killed_Players, N_Ts, D_Ws, Ch_buf.New_Walls);
			for (size_t j = 0; j < N_Ts.size(); j++)
				Ch_buf.Modifyed_Walls.push_back(make_pair(this->Current_Game.Walls[N_Ts[j].first],N_Ts[j].second));
			for (size_t j = 0; j < D_Ws.size(); j++)
				Ch_buf.Modifyed_Walls.push_back(make_pair(this->Current_Game.Walls[D_Ws[j]], Wall(Segment2D <double>(Point2D <double>(0, 0), Point2D <double>(0, 0)), -1, -1)));
			Ch += Ch_buf;
		}
	}
	for (size_t i = 0; i < this->Current_Game.Rockets.size(); i++) {
		if (this->Current_Game.Rockets[i].Explode()) {
			Clear(Ch_buf);
			Rocket_Explosion(i, K_Ps, N_Ts, D_Ws, N_Ws);
			for (size_t j = 0; j < N_Ts.size(); j++)
				Ch_buf.Modifyed_Walls.push_back(make_pair(this->Current_Game.Walls[N_Ts[j].first], N_Ts[j].second));
			for (size_t j = 0; j < D_Ws.size(); j++)
				Ch_buf.Modifyed_Walls.push_back(make_pair(this->Current_Game.Walls[D_Ws[j]], Wall(Segment2D <double>(Point2D <double>(0, 0), Point2D <double>(0, 0)), -1, -1)));
			Ch += Ch_buf;
		}
	}

	for (size_t i = 0; i < this->Current_Game.Players.size(); i++) {
		if (this->Current_Game.Players[i].Alive) {
			for (size_t j = 0; j < this->Current_Game.Bonuses.size(); j++) {
				if (Intersect(this->Current_Game.Players[i], this->Current_Game.Bonuses[j], dt)) {
					Ch.Collected_Bonuses.push_back(j);
					if (this->Current_Game.Bonuses[j].Rocket)
						this->Current_Game.Players[i].Gotta_Rocket();
					if (this->Current_Game.Bonuses[j].Bomb)
						this->Current_Game.Players[i].Gotta_Bomb();
				}
			}
		}
	}

	for (size_t i = 0; i < this->Current_Game.Players.size(); i++) {
		if (this->Current_Game.Players[i].Alive)
			this->Current_Game.Players[i].UPD(dt);
	}
	Wall_Prolong_All();

	for (size_t i = 0; i < this->Current_Game.Bombs.size(); i++)
		this->Current_Game.Bombs[i].UPD(dt);
	for (size_t i = 0; i < this->Current_Game.Rockets.size(); i++)
		this->Current_Game.Rockets[i].UPD(dt);

	set < int > Temp(Ch.Killed_Players.begin(), Ch.Killed_Players.end());
	Ch.Killed_Players = vector < int >(Temp.begin(), Temp.end());

	St.Players = this->Current_Game.Players;
	return;
}

void Game_Engine::_UPD_Client(const double dt) {
	for (size_t i = 0; i < this->Current_Game.Players.size(); i++) {
		if (this->Current_Game.Players[i].Alive)
			this->Current_Game.Players[i].UPD(dt);
	}
	Wall_Prolong_All();
	for (size_t i = 0; i < this->Current_Game.Bombs.size(); i++)
		this->Current_Game.Bombs[i].UPD(dt);
	for (size_t i = 0; i < this->Current_Game.Rockets.size(); i++)
		this->Current_Game.Rockets[i].UPD(dt);
	return;
}

void Game_Engine::UPD(const double dt) {
	State _St;
	Changes _Ch;
	_UPD(dt, _St, _Ch);
	this->Game_State += _St;
	this->Game_Changes += _Ch;
	return;
}

void Game_Engine::UPD_Client(const double dt) {
	_UPD_Client(dt);
	return;
}

bool Game_Engine::Game_Over(int &Win_Team) {
	set < int > Alive_Teams;
	Win_Team = -1;
	for (size_t i = 0; i < this->Current_Game.Players_Ammount; i++) {
		if (this->Current_Game.Players[i].Alive) {
			Alive_Teams.insert(this->Current_Game.Players[i].Team_Number);
			Win_Team = this->Current_Game.Players[i].Team_Number;
		}
	}
	return (Alive_Teams.size() == 1);
}

void Game_Engine::Start_Game(const int &_Players_Ammount, State &St) {
	this->Current_Game.Clear();
	this->Current_Game.Start(Player_Generate(_Players_Ammount));
	St.Players = this->Current_Game.Players;
	return;
}

void Game_Engine::Start_Game_Client(const State &St) {
	this->Current_Game.Clear();
	this->Current_Game.Start(St.Players);
	return;
}

void Game_Engine::Get_Changes_ACC(Changes &Ch) {
	Ch = this->Game_Changes;
	Clear(this->Game_Changes);
	return;
}

void Game_Engine::Update_Changes_ACC(const Changes &Ch) {
	PLayer_Kill(Ch.Killed_Players);
	Wall_Add(Ch.New_Walls);
	Wall_Modify(Ch.Modifyed_Walls);
	Bomb_Add(Ch.Placed_Bomb);
	Bomb_Delete(Ch.Exploded_Bombs);
	Rocket_Add(Ch.Placed_Rocket);
	Rocket_Delete(Ch.Exploded_Rockets);
	Bonus_Add(Ch.Placed_Bonuses);
	Bonus_Delete(Ch.Collected_Bonuses);
	return;
}

void Game_Engine::Get_Changes_NACC(State &St) {
	St = this->Game_State;
	Clear(this->Game_State);
	return;
}

void Game_Engine::Update_Changes_NACC(const State &St) {
	this->Current_Game.Players = St.Players;
	Wall_Prolong_All();
}
