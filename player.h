
struct Player
{
    void draw(Deck &deck);
    void discardWorstCard();

    vector<Card> hand;
};
