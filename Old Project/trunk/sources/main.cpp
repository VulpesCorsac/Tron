#include "..\stdafx.h"
#include "..\Headers\Game.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    Game* game = new Game();
    game->Run();

    return 0;
}
