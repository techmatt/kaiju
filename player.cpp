
#include "main.h"

void Player::draw(Deck &deck)
{
    while (hand.size() <= 4)
    {
        if (deck.cards.size() == 0)
        {
            return;
        }
        hand.push_back(deck.cards[deck.cards.size() - 1]);
        deck.cards.pop_back();
    }
}

void Player::discardWorstCard()
{
    auto cardUtility = [](const Card &c)
    {
        return c.colors[0] + c.colors[1] + c.colors[2];
    };
    auto cardSort = [&](const Card &a, const Card &b)
    {
        return cardUtility(a) > cardUtility(b);
    };

    random_shuffle(hand.begin(), hand.end());
    sort(hand.begin(), hand.end(), cardSort);

    hand.pop_back();
}
