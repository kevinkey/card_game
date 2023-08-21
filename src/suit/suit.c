#include "suit.h"

char suit_text(suit_t * suit)
{
    switch (suit->name)
    {
        case SUIT_CLUBS: return 'C';
        case SUIT_DIAMONDS: return 'D';
        case SUIT_HEARTS: return 'H';
        case SUIT_SPADES: return 'S';
    }

    return 'X';
}

void suit_draw(suit_t * suit)
{

}
