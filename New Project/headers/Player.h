#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "stdafx.h"

class Player {
public:
	// Player Data
	LightCycle MyCycle; // Current Point and direction
	Init_Constants* Constants; // Constants
	int Player_Number; // PLayer number
	int Team_Number; // Team number
	bool Alive; // Alive?
	void Kill(void); // Kill player


	// Bombs
	int Bomb_Ammount; // Bomb ammount
	void Gotta_Bomb(void); // Increase bomb ammount
	Bomb Place_Bomb(void); // Place Bomb

	// Rockets
	int Rocket_Ammount; // Rocket ammount
	void Gotta_Rocket(void); // Increase rocket ammount
	Rocket Shoot_Rocket(void); // Shoot Rocket;
	
	Player(const Point2D < double > &St_Point, const Vector2D < double > &St_Direction, Init_Constants* _Constants);
	~Player();
};

#endif // PLAYER_H_INCLUDED
