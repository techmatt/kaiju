
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
    CardType type;
    bool colors[ColorCount];
};

struct Deck
{
    void init();
};