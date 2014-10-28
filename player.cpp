
#include "main.h"

void Player::draw(Deck &deck, bool initialDraw)
{
    //
    // TODO: parameterize max hand size
    //
    while (hand.size() < 4)
    {
        if (deck.cards.size() == 0)
        {
            if (verbose) cout << id << " has no cards left to draw" << endl;
            return;
        }
        hand.push_back(deck.cards[deck.cards.size() - 1]);
        deck.cards.pop_back();

        if (verbose && !initialDraw) cout << id << " draws " << hand[hand.size() - 1].toString() << endl;
    }
}

void Player::discardMonsterAttackCard(const Card &c)
{
    int cardIndex = findFirstIndex(hand, c);
    Assert(cardIndex != -1, "card not found in hand!");

    removeSwap(hand, cardIndex);
    
    if (verbose) cout << id << " attacks with " << c.toString() << endl;
}

void Player::discardWorstCard()
{
    auto cardUtility = [](const Card &c)
    {
        int sum = c.colors[0] + c.colors[1] + c.colors[2];
        if (AIDiscardsSemiRandomly && sum <= 4)
            sum = 0;

        return sum;
    };
    auto cardSort = [&](const Card &a, const Card &b)
    {
        return cardUtility(a) > cardUtility(b);
    };

    random_shuffle(hand.begin(), hand.end());

    stable_sort(hand.begin(), hand.end(), cardSort);

    if (verbose) cout << "ACTION: " << id << " discards " << hand[hand.size() - 1].toString() << endl;

    hand.pop_back();
}
