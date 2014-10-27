
struct Player
{
    void draw(Deck &deck, bool initialDraw);
    void discardWorstCard();
    void discardMonsterAttackCard(const Card &c);
    
    string toString() const
    {
        if (hand.size() == 0) return "";

        string result;
        for (const Card &c : hand)
        {
            result += c.toString() + ",";
        }
        result.pop_back();
        return result;
    }

    string id;
    vector<Card> hand;
};
