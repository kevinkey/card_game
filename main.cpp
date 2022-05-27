#include <iostream>
#include "deck.h"
#include "card.h"
#include "suit.h"

int main()
{
    deck_t deck;
    deck.shuffle();
    deck.to_str();
}
