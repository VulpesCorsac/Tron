#include "stdafx.h"
#include "headers\InitConstants.h"

bool Init_Constants::Check() {
	if (this->Field_Width <= 0) {
		std::cerr << "Field_Width isn't positive!" << std::endl;
		return false;
	}
	if (this->Field_Length <= 0) {
		std::cerr << "Field_Length isn't positive!" << std::endl;
		return false;
	}
	if (this->Wall_Width < 0) {
		std::cerr << "Wall_Width is negative!" << std::endl;
		return false;
	}
	if (this->LightCycle_Length < 0) {
		std::cerr << "LightCycle_Length is negative!" << std::endl;
		return false;
	}
	if (this->LightCycle_Width < 0) {
		std::cerr << "LightCycle_Width is negative!" << std::endl;
		return false;
	}
	if (this->LightCycle_DefaultSpeed <= 0) {
		std::cerr << "LightCycle_DefaultSpeed isn't positive!" << std::endl;
		return false;
	}
	if (this->Rocket_Speed <= 0) {
		std::cerr << "Rocket_Speed isn't positive!" << std::endl;
		return false;
	}
	if (this->Rocket_Length <= 0) {
		std::cerr << "Rocket_Length isn't positive!" << std::endl;
		return false;
	}
	if (this->Rocket_Default_Ammount < 0) {
		std::cerr << "Rocket_Default_Ammount is negative!" << std::endl;
		return false;
	}
	if (this->Bomb_Time <= 0) {
		std::cerr << "Bomb_Time isn't positive!" << std::endl;
		return false;
	}
	if (this->Bomb_Radius <= 0) {
		std::cerr << "Bomb_Radius isn't positive!" << std::endl;
		return false;
	}
	if (this->Bomb_Default_Ammount < 0) {
		std::cerr << "Bomb_Default_Ammount is negative!" << std::endl;
		return false;
	}
	if (this->resX <= 0) {
		std::cerr << "ResolutionX isn't positive!" << std::endl;
		return false;
	}
	if (this->resY <= 0) {
		std::cerr << "ResolutionY isn't positive!" << std::endl;
		return false;
	}
	return true;
}

void Init_Constants::Init_from_config_file() {
	if (freopen("config.cfg", "r", stdin) == NULL) {
		std::cerr << "No config.cfg file was found!" << std::endl;
		throw(-1);
	}

	std::string s;

	while (std::cin >> s) {
		if (s == "Field_Width")
			std::cin >> this->Field_Width;
		else if (s == "Field_Length")
			std::cin >> this->Field_Length;
		else if (s == "Wall_Width")
			std::cin >> this->Wall_Width;
		else if (s == "LightCycle_Length")
			std::cin >> this->LightCycle_Length;
		else if (s == "LightCycle_Width")
			std::cin >> this->LightCycle_Width;
		else if (s == "LightCycle_DefaultSpeed")
			std::cin >> this->LightCycle_DefaultSpeed;
		else if (s == "Rocket_Speed")
			std::cin >> this->Rocket_Speed;
		else if (s == "Rocket_Length")
			std::cin >> this->Rocket_Length;
		else if (s == "Rocket_Default_Ammount")
			std::cin >> this->Rocket_Default_Ammount;
		else if (s == "Bomb_Time")
			std::cin >> this->Bomb_Time;
		else if (s == "Bomb_Radius")
			std::cin >> this->Bomb_Radius;
		else if (s == "Bomb_Default_Ammount")
			std::cin >> this->Bomb_Default_Ammount;
		else if (s == "ResolutionX")
			std::cin >> this->resX;
		else if (s == "ResolutionY")
			std::cin >> this->resY;
		else
			std::cerr << "Error in reading config.cfg file: unknown attribte:" << s << std::endl;

		std::getline(std::cin, s);
	}

	fclose(stdin);
	if (!Check()) {
		std::cerr << "Constant check failed!" << std::endl;
		throw - 1;
	}
}

Init_Constants::Init_Constants() {
	Init_from_config_file();
}

Init_Constants::~Init_Constants() {

}