
#include "main.h"

void Deck::init(const Parameters &params)
{
    cards.clear();

    //
    // add pure cards
    //
    for (int cardinality = 1; cardinality <= 7; cardinality++)
    {
        //
        // read count from file, ex. pure1Count = 2
        //
        int instances = params.getInt("pure" + to_string(cardinality) + "Count");
        for (int instance = 0; instance < instances; instance++)
        {
            cards.push_back(Card(CardTypePure, cardinality, 0, 0));
            cards.push_back(Card(CardTypePure, 0, cardinality, 0));
            cards.push_back(Card(CardTypePure, 0, 0, cardinality));
        }
    }

    //
    // add double cards
    //
    for (int cardinality = 1; cardinality <= 3; cardinality++)
    {
        //
        // read count from file, ex. double1Count = 2
        //
        int instances = params.getInt("double" + to_string(cardinality) + "Count");
        for (int instance = 0; instance < instances; instance++)
        {
            cards.push_back(Card(CardTypePure, cardinality, cardinality, 0));
            cards.push_back(Card(CardTypePure, 0, cardinality, cardinality));
            cards.push_back(Card(CardTypePure, cardinality, 0, cardinality));
        }
    }

    //
    // add triple cards
    //
    for (int cardinality = 1; cardinality <= 3; cardinality++)
    {
        //
        // read count from file, ex. triple1Count = 1
        //
        int instances = params.getInt("triple" + to_string(cardinality) + "Count");
        for (int instance = 0; instance < instances; instance++)
        {
            cards.push_back(Card(CardTypePure, cardinality, cardinality, cardinality));
        }
    }

    shuffle();
}

void Deck::shuffle()
{
    random_shuffle(cards.begin(), cards.end());
}
