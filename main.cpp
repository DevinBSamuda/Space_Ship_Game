#include "Game.h"
#include <iostream>
#include <time.h>

int main()
{

    // init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    game.run();

    // end of application
    return 0;
}
