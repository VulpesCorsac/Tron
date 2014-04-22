#include "stdafx.h"
#include "..\Headers\Game.h"
#include "..\headers\Client.h"
#include "..\headers\Server.h"


int main(int argc, char** argv) {
 //   glutInit(&argc, argv);

 //   Game* game = new Game();
//    game->Run();
    CServer vovan;
    vovan.think();
//    CClient vov;
 //   vov.connect("127.0.0.1");
    return 0;
}
