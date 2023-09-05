#ifndef CARD_H
#define CARD_H

#include "type.h"
#include "suit.h"

extern GLfloat Card_Size[2];

typedef enum
{
    CARD_A,
    CARD_2,
    CARD_3,
    CARD_4,
    CARD_5,
    CARD_6,
    CARD_7,
    CARD_8,
    CARD_9,
    CARD_T,
    CARD_J,
    CARD_Q,
    CARD_K,
    CARD_NUM,
} card_name_t;

typedef struct
{
    card_name_t name;
    suit_t * suit;
    GLfloat pos[2];
    bool facedown;
} card_t;

void card_init(card_t * card, suit_t * suit, card_name_t name);
bool card_within_bounds(card_t * card, GLfloat x, GLfloat y);
void card_draw(card_t * card);
char * card_text(card_t * card);
int card_diff(card_t * card_a, card_t * card_b);

#endif
