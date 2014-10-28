
#include "main.h"

void testParameter(const Parameters &baseParams, int gameCount, const string &parameterName, int lowValue, int highValue, int increment)
{
    ofstream file("parameterResults.csv");
    if (file.fail())
    {
        cout << " *** FAILED TO OPEN RESULTS FILE, IN USE BY ANOTHER APPLICATION ***" << endl;
        cin.get();
        return;
    }
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
        dist.simulate(newParams, gameCount, "");
        
        file << value << "," << dist.expectation(dist.scoreDistribution);
        for (int score = 0; score <= 20; score++)
            file << "," << dist.scoreDistribution[score];
        for (int monstersLeft = 0; monstersLeft <= 4; monstersLeft++)
            file << "," << dist.monsterLeftDistribution[monstersLeft];
        file << endl;
    }
}

void testMonsters(const Parameters &params, int gameCount, int monsterGroup)
{
    ofstream file("monsterResults.csv");
    if (file.fail())
    {
        cout << " *** FAILED TO OPEN RESULTS FILE, IN USE BY ANOTHER APPLICATION ***" << endl;
        cin.get();
        return;
    }
    file << "monsterGroup" << monsterGroup << ",expectation";

    for (int score = 0; score <= 20; score++)
        file << "," << "s" << score;
    for (int monstersLeft = 0; monstersLeft <= 4; monstersLeft++)
        file << "," << "m" << monstersLeft;
    file << endl;

    MonsterCollection monsters;
    monsters.init(params);
    const vector<Monster> &group = monsters.monsterGroups[monsterGroup];

    for (int monsterIndex = 0; monsterIndex < (int)group.size(); monsterIndex++)
    {
        string name = group[monsterIndex].name;
        cout << endl << "*** testing " << name << endl;
        
        GameDistribution dist;
        dist.simulate(params, gameCount, name);

        file << name << "," << dist.expectation(dist.scoreDistribution);
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

    const bool testSingleGame = true;
    const bool testParameters = false;
    const bool testMonsterGroup = false;

    const string testParameterName = "monsterTriplePure";
    const int testParameterLowValue = 6;
    const int testParameterHighValue = 10;
    const int testParameterIncrement = 1;
    const int testGameCount = 2000;

    const int monsterGroupIndex = 3;

    if (testSingleGame)
    {
        Game game;

        game.init(params, "");
        game.runToCompletion(params);
    }

    if (testParameters)
    {
        testParameter(params, testGameCount, testParameterName, testParameterLowValue, testParameterHighValue, testParameterIncrement);
    }

    if (testMonsterGroup)
    {
        testMonsters(params, testGameCount, monsterGroupIndex);
    }
}
