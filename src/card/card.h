#ifndef CARD_H
#define CARD_H

#include "suit.h"

typedef struct
{
    char name;
    suit_t * suit;
} card_t;

void card_init(card_t * card, suit_t * suit, char name);

#endif
