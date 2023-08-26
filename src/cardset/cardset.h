#ifndef CARDSET_H
#define CARDSET_H

#include "type.h"
#include "card.h"

typedef struct
{
    card_t ** set;
    size_t count;
    GLfloat pos[2];
    GLfloat offset[2];
    bool hide_empty;
} cardset_t;

void cardset_init(cardset_t * cardset);
void cardset_insert(cardset_t * cardset, card_t * card, int index);
void cardset_push(cardset_t * cardset, card_t * card);
card_t * cardset_remove(cardset_t * cardset, int index);
card_t * cardset_pop(cardset_t * cardset);
card_t * cardset_head(cardset_t * cardset);
card_t * cardset_tail(cardset_t * cardset);
void cardset_shuffle(cardset_t * cardset);
void cardset_draw(cardset_t * cardset);
bool cardset_within_bounds(cardset_t * cardset, GLfloat x, GLfloat y, int * index);
void cardset_transfer(cardset_t * dest, cardset_t * src);

#endif
