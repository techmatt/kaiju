
struct GameDistribution
{
    GameDistribution()
    {
        for (int score = 0; score <= 20; score++)
            scoreDistribution[score] = 0.0;
        for (int monsterCount = 0; monsterCount <= 5; monsterCount++)
            monsterLeftDistribution[monsterCount] = 0.0;
    }
    void simulate(const Parameters &params, int gameCount);
    
    static void normalize(map<int, double> &m);
    static double expectation(const map<int, double> &m);

    map<int, double> scoreDistribution;
    map<int, double> monsterLeftDistribution;
};