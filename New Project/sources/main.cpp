#include <stdafx.h>
#include "..\Headers\gengine.h"
#include "..\Headers\Game.h"
#include "..\headers\Client.h"
#include "..\headers\Server.h"


//temporary stuff to fix linking


void Game_Engine::Get_Changes_ACC(Changes &Ch){};
void Game_Engine::Update_Changes_ACC(Changes &Ch){};
void Game_Engine::Get_Changes_NACC(State &St){};
void Game_Engine::Update_Changes_NACC(State &St){};
void Game_Engine::Start_Game(const int &_Players_Ammount, State &St){};

int main(int argc, char** argv) {
    glutInit(&argc, argv);

 //   Game* game = new Game();
//    game->Run();

	init_network();
	CGEngine* ge = new CGEngine(new Init_Constants());
	ge->start();
	return 0;
	
	
	/*
    init_network();
    int a;
    scanf("%d", &a);
    if(a ==1)
    {

    CClient vovan;
    vovan.connect("127.0.0.1");
    printf("%d", vovan.get_num());
    }
    if(a == 0)
    {
        CServer vovan;
        while(vovan.think())
            printf("wwww");

    }
    scanf("%d",&a);*/
	
//CClient vov;
 //   vov.connect("127.0.0.1");
    return 0;
}
