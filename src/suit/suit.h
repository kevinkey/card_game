#ifndef SUIT_H
#define SUIT_H

#include "type.h"

typedef enum
{
    SUIT_SPADES,
    SUIT_HEARTS,
    SUIT_CLUBS,
    SUIT_DIAMONDS,
} suit_name_t;

typedef enum
{
    SUIT_COLOR_RED,
    SUIT_COLOR_BLACK,
} suit_color_t;

typedef struct
{
    suit_name_t name;
    suit_color_t color;
    GLfloat rgb[3];
} suit_t;

char suit_text(suit_t * suit);
void suit_draw(suit_t * suit);

#endif
