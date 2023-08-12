#ifndef DECK_H
#define DECK_H

#include "type.h"
#include "card.h"
#include "suit.h"

#define DECK_NUM_SUITS 4u
#define DECK_NUM_CARDS 13u

typedef struct
{
    suit_t suit[DECK_NUM_SUITS];
    card_t card[DECK_NUM_SUITS][DECK_NUM_CARDS];
} deck_t;

void deck_init(deck_t * deck);

#endif
