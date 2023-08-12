#include "card.h"

void card_init(card_t * card, suit_t * suit, char name)
{
    card->name = name;
    card->suit = suit;
}