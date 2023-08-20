#include "solitaire.h"

void solitaire_init(solitaire_t * solitaire)
{
    deck_init(&solitaire->deck);

    for (int i = 0; i < countof(solitaire->set); i++)
    {
        cardset_init(&solitaire->set[i]);
    }

    cardset_t * deck = &solitaire->set[SOLITAIRE_SET_DECK];

    for (int i = 0; i < countof(solitaire->deck.card); i++)
    {
        cardset_push(deck, &solitaire->deck.card[i]);
        solitaire->deck.card[i].facedown = true;
    }

    cardset_shuffle(deck);

    for (int i = 0; i < 7; i++)
    {
        cardset_t * col = &solitaire->set[SOLITAIRE_SET_COL_0 + i];

        for (int j = 0; j < i; j++)
        {
            card_t * card = cardset_pop(deck);

            card->facedown = true;
            cardset_push(col, card);
        }

        card_t * card = cardset_pop(deck);
        card->facedown = false;
        cardset_push(col, card);
    }

    Card_Size[0] = (2.0f - (8.0f * 0.02f)) / 7.0f;
    Card_Size[1] = Card_Size[0] * 1.8f;

    GLfloat x = -0.99f;

    for (int i = SOLITAIRE_SET_COL_0; i <= SOLITAIRE_SET_COL_6; i++)
    {
        solitaire->set[i].pos[0] = x;
        x += 0.02f + Card_Size[0];

        solitaire->set[i].pos[1] = Card_Size[1] - 0.1f;
        solitaire->set[i].offset[1] = -0.1f;
    }

    solitaire->set[SOLITAIRE_SET_DECK].pos[0] = solitaire->set[SOLITAIRE_SET_COL_0].pos[0];
    solitaire->set[SOLITAIRE_SET_DISCARD].pos[0] = solitaire->set[SOLITAIRE_SET_COL_1].pos[0];
    solitaire->set[SOLITAIRE_SET_HOME_0].pos[0] = solitaire->set[SOLITAIRE_SET_COL_3].pos[0];
    solitaire->set[SOLITAIRE_SET_HOME_1].pos[0] = solitaire->set[SOLITAIRE_SET_COL_4].pos[0];
    solitaire->set[SOLITAIRE_SET_HOME_2].pos[0] = solitaire->set[SOLITAIRE_SET_COL_5].pos[0];
    solitaire->set[SOLITAIRE_SET_HOME_3].pos[0] = solitaire->set[SOLITAIRE_SET_COL_6].pos[0];

    solitaire->set[SOLITAIRE_SET_DECK].pos[1] = 0.95f;
    solitaire->set[SOLITAIRE_SET_DISCARD].pos[1] = 0.95f;
    solitaire->set[SOLITAIRE_SET_HOME_0].pos[1] = 0.95f;
    solitaire->set[SOLITAIRE_SET_HOME_1].pos[1] = 0.95f;
    solitaire->set[SOLITAIRE_SET_HOME_2].pos[1] = 0.95f;
    solitaire->set[SOLITAIRE_SET_HOME_3].pos[1] = 0.95f;
}

void solitaire_draw(solitaire_t * solitaire)
{
    for (int i = 0; i < countof(solitaire->set); i++)
    {
        cardset_draw(&solitaire->set[i]);
    }
}
