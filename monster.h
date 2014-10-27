
struct Monster
{
    Monster(const string &_name, int redStrength, int yellowStrength, int blueStrength, int _anyStrength)
    {
        name = _name;
        strength[ColorRed] = redStrength;
        strength[ColorYellow] = yellowStrength;
        strength[ColorBlue] = blueStrength;
        anyStrength = _anyStrength;
    }

    //
    // name is used for special-case monster-killing code
    //
    string name;

    //
    // colors required to kill. anyStrength can come from any color
    //
    int strength[ColorCount];
    int anyStrength;

    //
    // score tells you what score you would get if the players attempt
    // to kill this monster with the given cards. Normally this parameter
    // would be a vector, but since the AI just computes all 2^(4*N) possible
    // card combinations, it's faster to avoid the dynamic memory overhead
    // of std::vector in this one case.
    //
    int score(const Card* cards, int cardCount) const;
};

//
// MonsterCollection represents the complete set of monsters that are randomly drawn from each game
//
struct MonsterCollection
{
    void init(const Parameters &params);
    vector<Monster> chooseMonsters(int monsterCount);

    vector<Monster> monsters;
};

/*
People will just fight a monster expecting to fail to let everyone "mass discard". Is this a thing we want to avoid? Perhaps
when you fail, the monster goes away.

Random monster ideas (move this to google doc)

Requires at least X cards to kill
*/
