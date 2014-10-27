
struct Player
{
    void draw(Deck &deck);
    void discardWorstCard();
    
    string toString() const
    {
        string result;
        for (const Card &c : hand)
        {
            result += c.toString() + ",";
        }
        result.pop_back();
        return result;
    }

    vector<Card> hand;
};
