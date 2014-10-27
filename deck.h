
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
    CardType type;
    int colors[ColorCount];
};

struct Deck
{
    void init(const Parameters &params);
    void shuffle();

    vector<Card> cards;
};