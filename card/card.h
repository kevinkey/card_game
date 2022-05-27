#ifndef CARD_H
#define CARD_H

#include "type.h"
#include "suit.h"

class card_t {
    suit_t * suit;
    char card;
public:
    card_t (suit_t *, char);
    string to_str(void);
};

#endif
