#ifndef DECK_H
#define DECK_H

#include "type.h"
#include "suit.h"
#include "card.h"

class deck_t {
    list<suit_t *> suit;
    list<card_t *> card;
public:
    deck_t(void);
    void shuffle(void);
    string to_str(void);
};

#endif
