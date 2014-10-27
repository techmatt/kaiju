
#include "main.h"

void Game::init(const Parameters &params)
{
    if (verbose) cout << "Starting new game..." << endl;

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
    turn = 0;

    spentInformation = 0;
    desperationTurns = 0;

    done = false;

    displayGameState();
}

void Game::runToCompletion(const Parameters &params)
{
    while (!done)
    {
        processTurn(params);
        activePlayer = (activePlayer + 1) % players.size();
    }
}

void Game::displayGameState() const
{
    if (!verbose) return;

    cout << endl << "*** game turn: " << turn << endl;
    cout << "score: " << score << endl;
    cout << "information tokens: " << informationTokens << endl;
    cout << "AI spent tokens: " << spentInformation << endl;
    cout << "desperation turns: " << desperationTurns << endl;
    deck.displayGameState();

    for (int playerIndex = 0; playerIndex < (int)players.size(); playerIndex++)
    {
        if (playerIndex == activePlayer) cout << " * ";
        cout << "P" << playerIndex << ": " << players[playerIndex].toString() << endl;
    }
    for (int monsterIndex = 0; monsterIndex < (int)monsters.size(); monsterIndex++)
    {
        cout << "M" << monsterIndex << ": " << monsters[monsterIndex].toString();
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

void Game::processTurn(const Parameters &params)
{
    Player &p = players[activePlayer];

    if (spentInformation >= params.getInt("spentInformationRequirement"))
    {
        vector< MonsterFightData > perMonsterCards = findBestSubsetPerMonster();
        int monsterToFight = -1;
        for (int monsterIndex = 0; monsterIndex < (int)monsters.size(); monsterIndex++)
        {

        }
    }

    if (informationTokens > 0)
        spendInformation();
    else
        discardWorstCard();

    
}

vector<MonsterFightData> Game::findBestSubsetPerMonster() const
{
    vector< MonsterFightData > perMonsterCards(monsters.size());
    Assert(players.size() == 4, "TODO: generalize over player size better");
    if (players.size() == 4)
    {
        //
        // iterate through all possible subsets of cards (except all 0's)
        //
        pair<Card, int> subsetCards[16];
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
                            subsetCards[subsetCardCount++] = make_pair(hand[cardIndex], playerIndex);
                        }
                    }
                }
            }

            //
            // test this subset of cards against each monster
            //
            for (int monsterIndex = 0; monsterIndex < (int)monsters.size(); monsterIndex++)
            {
                int monsterScore = monsters[monsterIndex].score(subsetCards, subsetCardCount);
                double overallScore = monsterScore + 1.0 - subsetCardCount;
                if (monsterScore > 0 && overallScore > perMonsterCards[monsterIndex].overallScore)
                {
                    perMonsterCards[monsterIndex].cards = vector< pair<Card, int> >(subsetCards, subsetCards + subsetCardCount);
                    perMonsterCards[monsterIndex].monsterScore = monsterScore;
                    perMonsterCards[monsterIndex].overallScore = overallScore;
                }
            }
        }
    }
    return perMonsterCards;
}