
#include "main.h"

int Test::testMonsterSubsetDifficultyTrial(const Parameters &params, const Monster &monster, int subsetSize, int playerCount, int handSize)
{
    Deck deck;
    deck.init(params);

    vector< pair<Card, int> > totalCards;
    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++)
    {
        for (int handIndex = 0; handIndex < handSize; handIndex++)
        {
            totalCards.push_back(make_pair(deck.cards.back(), playerIndex));
            deck.cards.pop_back();
        }
    }

    const int totalCardCount = (int)totalCards.size();
    int totalSubsets = (1 << totalCardCount);
    pair<Card, int> subsetCards[32];

    for (int subsetIndex = 1; subsetIndex < totalSubsets; subsetIndex++)
    {
        //
        // accumulate all the cards in this subset
        //
        int subsetCardCount = 0;
        for (int cardIndex = 0; cardIndex < totalCardCount; cardIndex++)
        {
            if (subsetIndex & (1 << cardIndex))
                subsetCards[subsetCardCount++] = totalCards[cardIndex];
        }

        if (subsetCardCount <= subsetSize)
        {
            int score = monster.score(subsetCards, subsetCardCount);
            if (score == 5)
                return 1;
        }
    }
    return 0;
}

//
// tests the probability of there being subset S of C randomly-drawn cards that can perfectly kill a monster.
// |S| = subsetSize, |C| = handSize * playerCount.
//
double Test::testMonsterSubsetDifficulty(const Parameters &params, const Monster &monster, int subsetSize, int playerCount, int handSize, int trialCount)
{
    int success = 0;

    for (int trialIndex = 0; trialIndex < trialCount; trialIndex++)
    {
        success += testMonsterSubsetDifficultyTrial(params, monster, subsetSize, playerCount, handSize);
    }
    return (double)success / (double)trialCount;
}

void Test::testParameter(const Parameters &baseParams, int gameCount, const string &parameterName, int lowValue, int highValue, int increment)
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

void Test::testMonsters(const Parameters &params, int gameCount, int monsterGroup)
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
