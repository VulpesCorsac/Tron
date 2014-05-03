#include "stdafx.h"
#include "Headers\Game.h"
#include "Headers\Client.h"
#include "Headers\Server.h"


int main(int argc, char** argv) {
   // glutInit(&argc, argv);

    //Game* game = new Game();
  //  game->Run();

   // CServer vovan; plz no vovan here, gtfo from mai main
 //   vovan.think();
//    CClient vov;
 //   vov.connect("127.0.0.1"); 


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
