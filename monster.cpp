
#include "main.h"

void MonsterCollection::init(const Parameters &params)
{
    int monsterBasicDouble = params.getInt("monsterBasicDouble");
    int monsterBasicTriple = params.getInt("monsterBasicTriple");

    monsters.push_back(Monster("doubleA", monsterBasicDouble, monsterBasicDouble, 0, 0));
    monsters.push_back(Monster("doubleB", monsterBasicDouble, 0, monsterBasicDouble, 0));
    monsters.push_back(Monster("doubleC", 0, monsterBasicDouble, monsterBasicDouble, 0));

    monsters.push_back(Monster("triple", monsterBasicTriple, monsterBasicTriple, monsterBasicTriple, 0));
}

int Monster::score(const Card* cards, int cardCount) const
{
    int colorSum[ColorCount] = { 0, 0, 0 };

    for (int cardIndex = 0; cardIndex < cardCount; cardIndex++)
    {
        const Card &card = cards[cardIndex];
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
    random_shuffle(monsters.begin(), monsters.end());

    vector<Monster> result;
    for (int i = 0; i < monsterCount; i++)
    {
        result.push_back(monsters[i]);
    }
    return result;
}