#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player {
public:
	// Player Data
	LightCycle MyCycle; // Current Point and direction
	Init_Constants* Constants; // Constants
	int Player_Number; // PLayer number
	int Team_Number; // Team number
	bool Alive; // Alive?

	// Bombs
	int Bomb_Ammount; // Bomb ammount
	void Gotta_Bomb(void); // Increase bomb ammount
	Bomb Place_Bomb(void); // Place Bomb

	// Rockets
	int Rocket_Ammount; // Rocket ammount
	void Gotta_Rocket(void); // Increase rocket ammount
	Rocket Shoot_Rocket(void); // Shoot Rocket;
	
	// Game
	void UPD(const double &dt);
	void Turn(const double &aplha);
	void Turn(const bool &is_left_turn);
	void SpeedUp(const double &New_Speed);
	void Kill(void); // Kill player

	Player(const Point2D < double > &St_Point, const Vector2D < double > &St_Direction, Init_Constants* _Constants);
	Player();
	~Player();
	
	Player &operator = (const Player &Player1);
	friend bool operator == (const Player &Player1, const Player &Player2);
	friend bool operator != (const Player &Player1, const Player &Player2);
};

#endif // PLAYER_H_INCLUDED
