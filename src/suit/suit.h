#ifndef SUIT_H
#define SUIT_H

#include "type.h"

typedef struct
{
    char const * name;
    GLfloat color[3];
} suit_t;

void suit_draw(suit_t * suit);

#endif
