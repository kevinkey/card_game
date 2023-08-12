#include "deck.h"

static char const * suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
static char const cards[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

void deck_init(deck_t * deck)
{
    for (uint8_t j = 0u; j < countof(suits); j++)
    {
        suit_init(&deck->suit[j], suits[j]);

        for (uint8_t i = 0u; i < countof(cards); i++)
        {
            card_init(&deck->card[j][i], &deck->suit[j], cards[i]);
        }
    }
}
