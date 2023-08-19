#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include "type.h"
#include "deck.h"
#include "cardset.h"

typedef enum
{
    SOLITAIRE_SET_DECK,
    SOLITAIRE_SET_DISCARD,
    SOLITAIRE_SET_HOME_0,
    SOLITAIRE_SET_HOME_1,
    SOLITAIRE_SET_HOME_2,
    SOLITAIRE_SET_HOME_3,
    SOLITAIRE_SET_COL_0,
    SOLITAIRE_SET_COL_1,
    SOLITAIRE_SET_COL_2,
    SOLITAIRE_SET_COL_3,
    SOLITAIRE_SET_COL_4,
    SOLITAIRE_SET_COL_5,
    SOLITAIRE_SET_COL_6,
    SOLITAIRE_SET_NUM,
} solitaire_set_t;

typedef struct
{
    deck_t deck;
    cardset_t set[SOLITAIRE_SET_NUM];
} solitaire_t;

void solitaire_init(solitaire_t * solitaire);
void solitaire_draw(solitaire_t * solitaire);

#endif
