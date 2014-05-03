#include <iostream>

#include "InitConstants.hpp"

using namespace std;

int main() {
    Init_Constants Init;
    cout << Init.Field_Width << endl;
    cout << Init.Field_Width << endl;
    cout << Init.Field_Length << endl;
    cout << Init.Wall_Width << endl;
    cout << Init.LightCycle_Length << endl;
    cout << Init.LightCycle_Width << endl;
    cout << Init.LightCycle_DefaultSpeed << endl;
    cout << Init.Rocket_Speed << endl;
    cout << Init.Rocket_Length << endl;
    cout << Init.Bomb_Time << endl;
    cout << Init.Bomb_Radius << endl;

    return 0;
}
