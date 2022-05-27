#include "suit.h"

suit_t::suit_t(string name)
{
    this->name = name;
}

string suit_t::to_str(void)
{
    return this->name;
}
