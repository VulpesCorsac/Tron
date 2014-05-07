#ifndef INITCONSTANTS_H_INCLUDED
#define INITCONSTANTS_H_INCLUDED

class Init_Constants {
private:
	// Assertion of constant values
	bool Check();

public:
    // Field Constants
    double Field_Width;
    double Field_Length;

    // Wall Constants
    double Wall_Width;

    // LeghtCycle Constants
    double LightCycle_Length;
    double LightCycle_Width;
    double LightCycle_DefaultSpeed;

    // Rocket Constants //lol rockets
    double Rocket_Speed;
    double Rocket_Length;

    //Bomb Constants
    double Bomb_Time;
    double Bomb_Radius;

	//Graphics Constants
	int resX, resY;

    // Initing constants
	void Init_from_config_file();

    // Constructor
	Init_Constants();

    // Destructor
	~Init_Constants();
};

#endif // INITCONSTANTS_H_INCLUDED
