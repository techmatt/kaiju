
enum CardType
{
    CardTypePure,
    CardTypeDouble,
    CardTypeTriple,
};

enum Color
{
    ColorRed,
    ColorYellow,
    ColorBlue,
    ColorCount
};

struct Card
{
    Card() {}
    Card(CardType _type, int red, int yellow, int blue)
    {
        type = _type;
        colors[ColorRed] = red;
        colors[ColorYellow] = yellow;
        colors[ColorBlue] = blue;
    }
    string toString() const
    {
        return "C" + to_string(colors[0]) + to_string(colors[1]) + to_string(colors[2]);
    }
    CardType type;
    int colors[ColorCount];
};

inline bool operator == (const Card &a, const Card &b)
{
    return a.colors[0] == b.colors[0] &&
           a.colors[1] == b.colors[1] &&
           a.colors[2] == b.colors[2];
}

struct Deck
{
    void init(const Parameters &params);
    void shuffle();

    void displayGameState() const;

    vector<Card> cards;
};