
class Test
{
public:
    static double testMonsterSubsetDifficulty(const Parameters &params, const Monster &monster, int subsetSize, int playerCount, int handSize, int trialCount);
    static void testParameter(const Parameters &baseParams, int gameCount, const string &parameterName, int lowValue, int highValue, int increment);
    static void testMonsters(const Parameters &params, int gameCount, int monsterGroup);

private:
    static int testMonsterSubsetDifficultyTrial(const Parameters &params, const Monster &monster, int subsetSize, int playerCount, int handSize);

};