
struct Game
{
    void init(const Parameters &params);

    void runToCompletion(const Parameters &params);
    void step(const Parameters &params);

    void spendInformation();
    void discardWorstCard();

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
