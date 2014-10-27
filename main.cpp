
#include "main.h"

void testParameter(const Parameters &baseParams, int gameCount, const string &parameterName, int lowValue, int highValue, int increment)
{
    ofstream file("results.csv");
    file << parameterName << ",expectation";

    for (int score = 0; score <= 20; score++)
        file << "," << "s" << score;
    for (int monstersLeft = 0; monstersLeft <= 4; monstersLeft++)
        file << "," << "m" << monstersLeft;
    file << endl;

    for (int value = lowValue; value <= highValue; value += increment)
    {
        cout << endl << "*** testing " << parameterName << " = " << value << endl;
        Parameters newParams = baseParams;
        newParams.setInt(parameterName, value);

        GameDistribution dist;
        dist.simulate(newParams, gameCount);
        
        file << value << "," << dist.expectation(dist.scoreDistribution);
        for (int score = 0; score <= 20; score++)
            file << "," << dist.scoreDistribution[score];
        for (int monstersLeft = 0; monstersLeft <= 4; monstersLeft++)
            file << "," << dist.monsterLeftDistribution[monstersLeft];
        file << endl;
    }
}

void main()
{
    //
    // randomize each game
    //
    srand((unsigned int)time(0));
    Parameters params("defaultParams.txt");

    const bool testSingleGame = false;
    if (testSingleGame)
    {
        Game game;

        game.init(params);
        game.runToCompletion(params);
    }

    const string testParameterName = "desperationMinScore";
    const int testParameterLowValue = 1;
    const int testParameterHighValue = 5;
    const int testParameterIncrement = 1;
    const int testGameCount = 1000;

    testParameter(params, testGameCount, testParameterName, testParameterLowValue, testParameterHighValue, testParameterIncrement);
}
