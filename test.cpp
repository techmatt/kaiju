
#include "main.h"

int Test::testMonsterSubsetDifficultyTrial(const Parameters &params, Deck &deck, const Monster &monster, int subsetSize, int playerCount, int handSize)
{
    deck.shuffle();

    int deckIndex = 0;
    vector< pair<Card, int> > totalCards;
    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++)
    {
        for (int handIndex = 0; handIndex < handSize; handIndex++)
        {
            totalCards.push_back(make_pair(deck.cards[deckIndex++], playerIndex));
        }
    }

    const int totalCardCount = (int)totalCards.size();
    int totalSubsets = (1 << totalCardCount);
    auto totalCardsCArray = &totalCards[0];
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
                subsetCards[subsetCardCount++] = totalCardsCArray[cardIndex];
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
    Deck deck;
    deck.init(params);

    int successTotal = 0;

#pragma omp parallel for
    for (int trialIndex = 0; trialIndex < trialCount; trialIndex++)
    {
        int success = testMonsterSubsetDifficultyTrial(params, deck, monster, subsetSize, playerCount, handSize);
        if (success)
            successTotal++;
    }
    
    return (double)successTotal / (double)trialCount;
}

void Test::testMonsterRange(const Parameters &params, int startRed, int endRed, int yellow, int blue, int trialCount)
{
    ofstream file("monsterResults.csv");
    if (file.fail())
    {
        cout << " *** FAILED TO OPEN RESULTS FILE, IN USE BY ANOTHER APPLICATION ***" << endl;
        cin.get();
        return;
    }

    file << "Monster";
    for (int subsetSize = 1; subsetSize <= 16; subsetSize++)
        file << ",s" << subsetSize;
    file << endl;

    for (int red = startRed; red <= endRed; red++)
    {
        Monster monster("temp", red, yellow, blue, 0);
        
        file << red << "-" << yellow << "-" << blue;

        for (int subsetSize = 1; subsetSize <= 16; subsetSize++)
        {
            cout << "testing red=" << red << ", subset=" << subsetSize << endl;
            file << ",";
            file << testMonsterSubsetDifficulty(params, monster, subsetSize, 4, 4, trialCount);
        }
        file << endl;
    }
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
