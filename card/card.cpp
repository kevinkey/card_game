#include "card.h"

card_t::card_t(suit_t * suit, char card)
{
    this->suit = suit;
    this->card = card;
}

string card_t::to_str(void)
{
    string card;

    card.append(this->suit->to_str(), 0, 1);
    card.append(1, this->card);

    return card;
}
