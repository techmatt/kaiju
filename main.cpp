
#include "main.h"

void main()
{
    //
    // randomize each game
    //
    srand((unsigned int)time(0));

    Game game;
    Parameters params("defaultParams.txt");

    game.init(params);
    game.runToCompletion(params);
}
