#ifndef INITIALCONSTANTS_HPP_INCLUDED
#define INITIALCONSTANTS_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <string>
#include <assert.h>

class Init_Constants {
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

    // Initing constants
    void Init_from_config_file() {
        if (freopen("config.cfg", "r", stdin) == NULL) {
            std::cerr << "No config.cfg file was found!" << std::endl;
            throw(-1);
        }

        std::string s;
        while (std::cin >> s) {
            if(s == "Field_Width") {
                    std::cin >> this->Field_Width;
                    assert(this->Field_Width > 0 && "Field_Width isn't positive");
            } else
            if(s == "Field_Length") {
                    std::cin >> this->Field_Length;
                    assert(this->Field_Length >= 0 && "Field_Length isn't positive");
            } else
            if(s == "Wall_Width") {
                    std::cin >> this->Wall_Width;
                    assert(this->Wall_Width >= 0 && "Wall_Width is negative");
            } else
            if(s == "LightCycle_Length") {
                    std::cin >> this->LightCycle_Length;
                    assert(this->LightCycle_Length >= 0 && "LightCycle_Length is negative");
            } else
            if(s == "LightCycle_Width") {
                    std::cin >> this->LightCycle_Width;
                    assert(this->LightCycle_Width >= 0 && "LightCycle_Width is negative");
            } else
            if(s == "LightCycle_DefaultSpeed") {
                    std::cin >> this->LightCycle_DefaultSpeed;
                    assert(this->LightCycle_DefaultSpeed > 0 && "LightCycle_DefaultSpeed isn't positive");
            } else {
                std::cerr << "Error in reading config.cfg file: unknown attribte" << std::endl;
                throw(-1);
            }

            std::getline(std::cin, s);
        }

        fclose(stdin);
    }

    // Constructor
    Init_Constants() {
        Init_from_config_file();
    }

    // Destructor
    ~Init_Constants() {

    }
};

#endif // INITIALCONSTANTS_HPP_INCLUDED
