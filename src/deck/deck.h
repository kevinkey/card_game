#ifndef DECK_H
#define DECK_H

#include "type.h"
#include "card.h"
#include "cardset.h"

typedef struct
{
    card_t card[52];
    cardset_t set;
    card_t * selected;
    GLfloat offset[2];
} deck_t;

void deck_init(deck_t * deck);
void deck_select_card(deck_t * deck, GLfloat x, GLfloat y);
void deck_move_card(deck_t * deck, GLfloat x, GLfloat y);
void deck_draw(deck_t * deck);

#endif
