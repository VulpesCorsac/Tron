#include <stdafx.h>
#include "..\Headers\gengine.h"
#include "..\Headers\Game.h"
#include "..\headers\Client.h"
#include "..\headers\Server.h"


int main(int argc, char** argv) {
    glutInit(&argc, argv);

 //   Game* game = new Game();
//    game->Run();
	
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
