#include "deck.h"
#include <iterator>

string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
char cards[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

static bool shuffle_compare(card_t * first, card_t * second)
{
    return true;
}

deck_t::deck_t(void)
{
    for(int i = 0; i < countof(suits); i++)
    {
        suit_t * s = new suit_t(suits[i]);

        suit.push_back(s);

        for(int j = 0; j < countof(cards); j++)
        {
            card.push_back(new card_t(s, cards[j]));
        }
    }
}

void deck_t::shuffle(void)
{
    card.sort(shuffle_compare);
}

string deck_t::to_str(void)
{
    for (auto it = begin(card); it != end(card); ++it)
        printf("%s ", (*it)->to_str().c_str());
    printf("\n");

    return "hello";
}
