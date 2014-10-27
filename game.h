
//
// for each monster, this stores the best subset of cards to kill that monster
//
struct MonsterFightData
{
    MonsterFightData()
    {
        monsterScore = 0;
        overallScore = 0.0;
    }

    //
    // cards needed to kill and associated index of the player who owns the card
    //
    vector< pair<Card, int> > cards;

    //
    // this is the score the players will gain if they fight the monster with these cards
    //
    int monsterScore;

    //
    // this is how good this subset in, factoring in monsterScore and the number of cards spent
    //
    double overallScore;
};

struct Game
{
    void init(const Parameters &params);

    void runToCompletion(const Parameters &params);
    void processTurn(const Parameters &params);

    void spendInformation();
    void discardWorstCard();
    void fightMonster(const Parameters &params, int monsterIndex, const vector< pair<Card, int> > &cards);

    vector<MonsterFightData> findBestSubsetPerMonster() const;

    void displayGameState(const Parameters &params) const;

    //
    // game state
    //

    Deck deck;
    int score;

    vector<Player> players;

    //
    // this contains only remaining monsters
    //
    vector<Monster> monsters;

    int informationTokens;

    int activePlayer;
    int turn;

    //
    // this is the number of information the AIs have spent since the previous
    // monster. When it reaches a threshold, they will try to kill a monster.
    //
    int spentInformation;

    //
    // this is the number of turns the players have gone since having enough information
    // but not having a perfect monster kill. At some point they will just kill a monster,
    // even if it isn't perfect.
    //
    int desperationTurns;

    bool done;
};
