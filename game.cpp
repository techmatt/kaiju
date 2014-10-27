
#include "main.h"

void Game::init(const Parameters &params)
{
    deck.init(params);
    score = 0;

    players.resize(params.getInt("playerCount"));
    for (Player &p : players)
        p.draw(deck);

    MonsterCollection monsterCollection;
    monsterCollection.init(params);
    monsters = monsterCollection.chooseMonsters(params.getInt("monsterCount"));

    informationTokens = params.getInt("startInformationCount");
    
    activePlayer = 0;

    spentInformation = 0;
    desperationTurns = 0;

    done = false;
}

void Game::runToCompletion(const Parameters &params)
{
    while (!done)
    {
        step(params);
    }
}

void Game::spendInformation()
{
    informationTokens--;
    spentInformation++;
}

void Game::discardWorstCard()
{
    players[activePlayer].discardWorstCard();
    informationTokens++;
}

void Game::step(const Parameters &params)
{
    /*
    AI pseudo-code
    if not enough information spent
        if information
            spend information
        else
            discard least-useful card
    if perfect monster kill possible
        kill monster
    else if enough desperationTurns have passed
        do imperfect monster kill on best monster possible
    */

    Player &p = players[activePlayer];

    if (spentInformation < params.getInt("spentInformationRequirement"))
    {
        if (informationTokens > 0)
        {
            spendInformation();
        }
        else
        {
            discardWorstCard();
        }
    }
    else
    {
        if (players.size() == 4)
        {
            //
            // iterate through all possible subsets of cards (except all 0's)
            //
            Card subsetCards[16];
            for (int subset = 1; subset <= 0xFFFF; subset++)
            {
                //
                // accumulate all the cards in this subset
                //
                int subsetCardCount = 0;
                for (int playerIndex = 0; playerIndex < 4; playerIndex++)
                {
                    for (int cardIndex = 0; cardIndex < 4; cardIndex++)
                    {
                        if (subset & (1 << (playerIndex * 4 + cardIndex)))
                        {
                            const auto &hand = players[playerIndex].hand;
                            if (cardIndex < (int)hand.size())
                            {
                                subsetCards[subsetCardCount++] = hand[cardIndex];
                            }
                        }
                    }
                }

                //
                // test all these cards against each monster
                //
            }
        }
    }

    activePlayer = (activePlayer + 1) % players.size();
}
