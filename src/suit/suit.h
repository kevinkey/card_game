#ifndef SUIT_H
#define SUIT_H

#include "type.h"

typedef struct
{
    char const * name;
} suit_t;


void suit_init(suit_t * suit, char const * name);

void suit_draw(suit_t * suit);

#endif
