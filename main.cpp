#include "Game.h"

int main()
{
    //Init srnad
    srand(static_cast<unsigned>(time(NULL)));

    //Init Game engine
    Game game;

    //Game Loop
    while (game.getWindowIsOpen() && !game.getEndGame())
    {
        //Update
        game.update();

        //Render
        game.render();
    }
    //End of Application
    return 0;
}