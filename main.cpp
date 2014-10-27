
#include "main.h"

void main()
{
    Game game;
    Parameters params("defaultParams.txt");

    game.init(params);
    game.runToCompletion(params);
}
