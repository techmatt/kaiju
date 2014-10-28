
#include "main.h"

void MonsterCollection::init(const Parameters &params)
{
    int monsterBasicPeak = params.getInt("monsterBasicPeak");
    int monsterBasicDouble = params.getInt("monsterBasicDouble");
    int monsterBasicTriple = params.getInt("monsterBasicTriple");

    monsterGroups[0].push_back(Monster("doubleA", monsterBasicDouble, monsterBasicDouble, 0, 0));
    monsterGroups[1].push_back(Monster("doubleB", monsterBasicDouble, 0, monsterBasicDouble, 0));
    monsterGroups[2].push_back(Monster("doubleC", 0, monsterBasicDouble, monsterBasicDouble, 0));

    monsterGroups[0].push_back(Monster("peakA", monsterBasicPeak, 0, 0, 0));
    monsterGroups[1].push_back(Monster("peakB", 0, monsterBasicPeak, 0, 0));
    monsterGroups[2].push_back(Monster("peakC", 0, 0, monsterBasicPeak, 0));

    monsterGroups[3].push_back(Monster("triple", monsterBasicTriple, monsterBasicTriple, monsterBasicTriple, 0));
}

int Monster::score(const pair<Card, int>* cards, int cardCount) const
{
    int colorSum[ColorCount] = { 0, 0, 0 };

    for (int cardIndex = 0; cardIndex < cardCount; cardIndex++)
    {
        const Card &card = cards[cardIndex].first;
        for (int colorIndex = 0; colorIndex < 3; colorIndex++)
            colorSum[colorIndex] += card.colors[colorIndex];
    }

    int excess = 0;
    
    for (int colorIndex = 0; colorIndex < 3; colorIndex++)
    {
        if (colorSum[colorIndex] >= strength[colorIndex])
        {
            excess += colorSum[colorIndex] - strength[colorIndex];
        }
        else
        {
            return 0;
        }
    }

    if (excess < anyStrength)
        return 0;

    excess -= anyStrength;

    //
    // TODO: parameterize score. Currently assumes 5,4,3,2,1,0 scale.
    //
    return max(0, 5 - excess);
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
        for (const Monster &m : monsters)
        {
            if (m.name == requiredMonster)
                return monsters;
        }
    }
    return vector<Monster>();
}