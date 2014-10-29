
#include "main.h"

void main()
{
    //
    // randomize each game
    //
    srand((unsigned int)time(0));
    Parameters params("defaultParams.txt");

    const bool testSingleGame = false;
    const bool testParameters = false;
    const bool testMonsterGroup = false;
    const bool testMonsterParameters = true;

    const string testParameterName = "monsterTriplePure";
    const int testParameterLowValue = 6;
    const int testParameterHighValue = 6;
    const int testParameterIncrement = 1;
    const int testGameCount = 100;

    const int monsterGroupIndex = 3;

    if (testSingleGame)
    {
        Game game;

        game.init(params, "");
        game.runToCompletion(params);
    }

    if (testParameters)
    {
        Test::testParameter(params, testGameCount, testParameterName, testParameterLowValue, testParameterHighValue, testParameterIncrement);
    }

    if (testMonsterGroup)
    {
        Test::testMonsters(params, testGameCount, monsterGroupIndex);
    }

    if (testMonsterParameters)
    {
        Test::testMonsterRange(params, 16, 16, 0, 0, 10000);
    }
}
