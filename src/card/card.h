#ifndef CARD_H
#define CARD_H

#include "type.h"
#include "suit.h"

extern GLfloat Card_Size[2];

typedef struct
{
    char name;
    suit_t const * suit;
    GLfloat pos[2];
    bool facedown;
} card_t;

void card_init(card_t * card, suit_t const * suit, char name);
bool card_within_bounds(card_t * card, GLfloat x, GLfloat y);
void card_draw(card_t * card);

#endif
