#include "stdafx.h"
#include "headers\Game.h"
#include "headers\Client.h"
#include "headers\Server.h"
#include "headers\gEngine.h"


int main(int argc, char** argv) {
//	glutInit(&argc, argv);

//	Game* game = new Game();
//	game->Run();

//	CServer vovan; // plz no vovan here, gtfo from mai main. Shkol'niki!
//	vovan.think();
//	CClient vov;
//	vov.connect("127.0.0.1"); 

	glutInit(&argc, argv);
	Init_Constants* Init = new Init_Constants();

	CGEngine* eng = new CGEngine(Init);
	eng->start();

    return 0;
}
