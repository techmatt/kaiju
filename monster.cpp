
#include "main.h"

void MonsterCollection::init(const Parameters &params)
{
    int monsterSingle = params.getInt("monsterSingle");
    int monsterDouble = params.getInt("monsterDouble");
    int monsterTriple = params.getInt("monsterTriple");
    int monsterTriplePure = params.getInt("monsterTriplePure");

    monsterGroups[0].push_back(Monster("doubleA", monsterDouble, monsterDouble, 0, 0));
    monsterGroups[1].push_back(Monster("doubleB", monsterDouble, 0, monsterDouble, 0));
    monsterGroups[2].push_back(Monster("doubleC", 0, monsterDouble, monsterDouble, 0));

    monsterGroups[0].push_back(Monster("peakA", monsterSingle, 0, 0, 0));
    monsterGroups[1].push_back(Monster("peakB", 0, monsterSingle, 0, 0));
    monsterGroups[2].push_back(Monster("peakC", 0, 0, monsterSingle, 0));

    monsterGroups[3].push_back(Monster("triple", monsterTriple, monsterTriple, monsterTriple, 0));
    monsterGroups[3].push_back(Monster("triplePure", monsterTriplePure, monsterTriplePure, monsterTriplePure, 0));
}

int Monster::score(const pair<Card, int>* cards, int cardCount) const
{
    int colorSum[ColorCount] = { 0, 0, 0 };

    if (name == "triplePure")
    {
        for (int cardIndex = 0; cardIndex < cardCount; cardIndex++)
        {
            if (cards[cardIndex].first.type != CardTypePure)
                return 0;
        }
    }

    for (int cardIndex = 0; cardIndex < cardCount; cardIndex++)
    {
        const Card &card = cards[cardIndex].first;
        for (int colorIndex = 0; colorIndex < 3; colorIndex++)
            colorSum[colorIndex] += card.colors[colorIndex];
    }

    int excess[ColorCount] = { 0, 0, 0 };
    
    for (int colorIndex = 0; colorIndex < 3; colorIndex++)
    {
        if (colorSum[colorIndex] >= strength[colorIndex])
        {
            excess[colorIndex] = colorSum[colorIndex] - strength[colorIndex];
        }
        else
        {
            return 0;
        }
    }

    int diamondCount = 0;
    for (int cardIndex = 0; cardIndex < cardCount; cardIndex++)
    {
        if (cards[cardIndex].first.type == CardTypeDiamond)
            diamondCount++;
    }
    
    //
    // diamonds remove excess
    //
    for (int diamondIndex = 0; diamondIndex < diamondCount; diamondIndex++)
    {
        int maxIndex = util::maxIndex(excess[0], excess[1], excess[2]);
        excess[maxIndex] = 0;
    }

    int totalExcess = excess[0] + excess[1] + excess[2];

    if (totalExcess < anyStrength)
        return 0;

    totalExcess -= anyStrength;

    //
    // TODO: parameterize score. Currently assumes 5,4,3,2,1,1,...,1 scale.
    //
    return max(1, 5 - totalExcess);
}

vector<Monster> MonsterCollection::chooseMonsters(int monsterCount)
{
    Assert(monsterCount == monsterGroupCount, "unexpected number of monsters");

    for (auto &group : monsterGroups)
        random_shuffle(group.begin(), group.end());

    vector<Monster> result;
    for (int i = 0; i < monsterCount; i++)
    {
        result.push_back(monsterGroups[i][0]);
    }
    return result;
}

vector<Monster> MonsterCollection::chooseMonsters(int monsterCount, const string &requiredMonster)
{
    while (true)
    {
        vector<Monster> monsters = chooseMonsters(monsterCount);
        if (requiredMonster == "")
            return monsters;

        for (const Monster &m : monsters)
        {
            if (m.name == requiredMonster)
                return monsters;
        }
    }
    return vector<Monster>();
}