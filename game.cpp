
#include "main.h"

void Game::init(const Parameters &params, const string &requiredMonster)
{
    if (verbose) cout << "Starting new game..." << endl;

    deck.init(params);
    score = 0;

    players.resize(params.getInt("playerCount"));
    
    int playerIndex = 0;
    for (Player &p : players)
    {
        p.id = "P" + to_string(playerIndex + 1);
        p.draw(deck, true);
        playerIndex++;
    }
        
    MonsterCollection monsterCollection;
    monsterCollection.init(params);
    monsters = monsterCollection.chooseMonsters(params.getInt("monsterCount"), requiredMonster);

    informationTokens = params.getInt("startInformationCount");
    
    activePlayer = 0;
    turn = 1;
    gameEndTurn = 1000;

    spentInformation = 0;
    desperationTurns = 0;

    done = false;
}

void Game::runToCompletion(const Parameters &params)
{
    while (!done)
    {
        if (verbose) cout << endl << "*** begin turn " << turn << endl;
        displayGameState(params);
        processTurn(params);
        activePlayer = (activePlayer + 1) % players.size();
        turn++;

        if (deck.cards.size() == 0 && gameEndTurn == 1000)
        {
            if (verbose) cout << "no cards left in deck, game ending in 4 turns" << endl;

            spentInformation = params.getInt("spentInformationRequirement");
            gameEndTurn = turn + 4;
        }

        if (turn >= gameEndTurn)
        {
            if (verbose) cout << "deck is empty and all turns elapsed, game over" << endl;
            done = true;
        }

        if (monsters.size() == 0)
        {
            if (verbose) cout << "no monsters left, game over" << endl;
            done = true;
        }

        if (verbose)
        {
            cout << "press enter to advance..." << endl;
            cin.get();
        }
    }

    if (verbose) cout << endl << "*** final game state. total turns: " << turn << endl;
    displayGameState(params);
}

void Game::displayGameState(const Parameters &params) const
{
    if (!verbose) return;

    cout << "score: " << score << endl;
    cout << "information tokens: " << informationTokens << endl;
    cout << "AI spent tokens: " << spentInformation << " / " << params.getInt("spentInformationRequirement") << endl;
    cout << "desperation turns: " << desperationTurns << endl;
    deck.displayGameState();

    cout << " -- players" << endl;
    for (int playerIndex = 0; playerIndex < (int)players.size(); playerIndex++)
    {
        if (playerIndex == activePlayer) cout << " * ";
        else cout << "   ";
        cout << players[playerIndex].id << ": " << players[playerIndex].toString() << endl;
    }

    cout << " -- monsters" << endl;
    for (int monsterIndex = 0; monsterIndex < (int)monsters.size(); monsterIndex++)
    {
        cout << "   " << monsters[monsterIndex].toString() << endl;
    }
}

void Game::spendInformation()
{
    if (verbose) cout << "ACTION: " << players[activePlayer].id << " spends an information" << endl;
    informationTokens--;
    spentInformation++;
}

void Game::discardWorstCard()
{
    players[activePlayer].discardWorstCard();
    players[activePlayer].draw(deck, false);
    informationTokens++;
}

void Game::fightMonster(const Parameters &params, int monsterIndex, const vector< pair<Card, int> > &cards)
{
    Monster &m = monsters[monsterIndex];
    int scoreGained = m.score(&cards[0], cards.size());
    score += scoreGained;

    if (verbose) cout << "ACTION: players fight " << m.toString() << " and score " << scoreGained << " points" << endl;

    Assert(scoreGained != 0, "Fighting monster with no score");

    for (auto &c : cards)
        players[c.second].discardMonsterAttackCard(c.first);

    for (auto &p : players)
        p.draw(deck, false);

    removeSwap(monsters, monsterIndex);

    if (verbose) cout << "players gain " << params.getInt("monsterVictoryInformation") << " information tokens" << endl;
    informationTokens += params.getInt("monsterVictoryInformation");

    spentInformation = 0;
    desperationTurns = 0;
}

void Game::processTurn(const Parameters &params)
{
    Player &p = players[activePlayer];

    if (spentInformation >= params.getInt("spentInformationRequirement"))
    {
        vector< MonsterFightData > perMonsterCards = findBestSubsetPerMonster();
        int monsterToFightIndex = -1;
        double bestOverallScore = 0.0;
        for (int monsterIndex = 0; monsterIndex < (int)monsters.size(); monsterIndex++)
        {
            if (verbose) cout << "Best score against " << monsters[monsterIndex].name << " -> " << perMonsterCards[monsterIndex].monsterScore << endl;

            if (perMonsterCards[monsterIndex].overallScore > bestOverallScore)
            {
                monsterToFightIndex = monsterIndex;
                bestOverallScore = perMonsterCards[monsterIndex].overallScore;
            }
        }

        if (monsterToFightIndex != -1)
        {
            int bestMonsterScore = perMonsterCards[monsterToFightIndex].monsterScore;
            if (bestMonsterScore == 5 ||
                deck.cards.size() == 0 ||
                (bestMonsterScore >= params.getInt("desperationMinScore") && desperationTurns >= params.getInt("desperationTurnThreshold")))
            {
                fightMonster(params, monsterToFightIndex, perMonsterCards[monsterToFightIndex].cards);
                return;
            }
        }

        //
        // we have enough information but not enough cards to kill a monster, so we're desperate
        //
        desperationTurns++;
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
                            subsetCards[subsetCardCount].first = hand[cardIndex];
                            subsetCards[subsetCardCount++].second = playerIndex;
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
                double overallScore = monsterScore + 1.0 - subsetCardCount * 0.001;
                if (monsterScore == 0.0)
                    overallScore = 0.0;

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