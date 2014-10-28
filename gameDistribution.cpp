
#include "main.h"

void GameDistribution::simulate(const Parameters &params, int gameCount, const string &requiredMonster)
{
#pragma omp parallel for
    for (int gameIndex = 0; gameIndex < gameCount; gameIndex++)
    {
        if (gameIndex % 100 == 0) cout << "game " << gameIndex << " / " << gameCount << endl;

        Game game;
        game.init(params, requiredMonster);
        game.runToCompletion(params);

        //
        // this is technically not thread safe, but I doubt it matters
        //
        scoreDistribution[game.score]++;
        monsterLeftDistribution[game.monsters.size()]++;
    }
    normalize(scoreDistribution);
    normalize(monsterLeftDistribution);
}

void GameDistribution::normalize(map<int, double> &m)
{
    double sum = 0.0;
    for (const auto &s : m)
        sum += s.second;

    Assert(sum != 0.0, "no values!");
    for (auto &s : m)
        s.second /= sum;
}

double GameDistribution::expectation(const map<int, double> &m)
{
    double result = 0.0;
    for (const auto &s : m)
        result += s.first * s.second;
    return result;
}