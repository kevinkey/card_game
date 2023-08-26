#include "solitaire.h"

static void set_select(solitaire_t * solitaire, solitaire_set_t set, GLfloat x, GLfloat y, int index)
{
    solitaire->previous_set = set;

    switch (set)
    {
        case SOLITAIRE_SET_DISCARD:
        case SOLITAIRE_SET_HOME_0:
        case SOLITAIRE_SET_HOME_1:
        case SOLITAIRE_SET_HOME_2:
        case SOLITAIRE_SET_HOME_3:
            if (solitaire->set[set].count > 0)
            {
                cardset_push(
                    &solitaire->set[SOLITAIRE_SET_SELECTED],
                    cardset_pop(&solitaire->set[set]));
            }
            break;
        case SOLITAIRE_SET_COL_0:
        case SOLITAIRE_SET_COL_1:
        case SOLITAIRE_SET_COL_2:
        case SOLITAIRE_SET_COL_3:
        case SOLITAIRE_SET_COL_4:
        case SOLITAIRE_SET_COL_5:
        case SOLITAIRE_SET_COL_6:
            if ((index < solitaire->set[set].count) && !solitaire->set[set].set[index]->facedown)
            {
                card_t * card;

                while ((card = cardset_remove(&solitaire->set[set], index)) != NULL)
                {
                    cardset_push(&solitaire->set[SOLITAIRE_SET_SELECTED], card);
                }
            }
            break;
    }

    if (solitaire->set[SOLITAIRE_SET_SELECTED].count > 0)
    {
        memcpy(
            solitaire->set[SOLITAIRE_SET_SELECTED].offset,
            solitaire->set[set].offset,
            sizeof(solitaire->set[set].offset));
        memcpy(
            solitaire->set[SOLITAIRE_SET_SELECTED].pos,
            solitaire->set[SOLITAIRE_SET_SELECTED].set[0]->pos,
            sizeof(solitaire->set[SOLITAIRE_SET_SELECTED].set[0]->pos));
        solitaire->offset[0] = solitaire->set[SOLITAIRE_SET_SELECTED].set[0]->pos[0] - x;
        solitaire->offset[1] = solitaire->set[SOLITAIRE_SET_SELECTED].set[0]->pos[1] - y;
    }
}

static void set_release(solitaire_t * solitaire, solitaire_set_t set, GLfloat x, GLfloat y, int index)
{
    card_t * card;

    printf("RELEASE: %d %d\n", set, index);

    switch (set)
    {
        case SOLITAIRE_SET_DECK:
            if (solitaire->previous_set == SOLITAIRE_SET_DECK)
            {
                if ((card = cardset_pop(&solitaire->set[SOLITAIRE_SET_DECK])) != NULL)
                {
                    card->facedown = false;
                    cardset_push(&solitaire->set[SOLITAIRE_SET_DISCARD], card);
                }
                else
                {
                    while ((card = cardset_pop(&solitaire->set[SOLITAIRE_SET_DISCARD])) != NULL)
                    {
                        card->facedown = true;
                        cardset_push(&solitaire->set[SOLITAIRE_SET_DECK], card);
                    }
                }
            }
            break;
        case SOLITAIRE_SET_HOME_0:
        case SOLITAIRE_SET_HOME_1:
        case SOLITAIRE_SET_HOME_2:
        case SOLITAIRE_SET_HOME_3:
            if (solitaire->set[SOLITAIRE_SET_SELECTED].count == 1)
            {
                card_t * head = solitaire->set[SOLITAIRE_SET_SELECTED].set[0];
                bool move_card;

                if (solitaire->set[set].count <= 0)
                {
                    move_card = (head->name == CARD_A);
                }
                else
                {
                    card_t * tail = solitaire->set[set].set[solitaire->set[set].count - 1u];
                    move_card = (card_diff(tail, head) == -1) && (tail->suit->name == head->suit->name);
                }

                if (move_card) cardset_transfer(
                    &solitaire->set[set],
                    &solitaire->set[SOLITAIRE_SET_SELECTED]);
            }
            break;
        case SOLITAIRE_SET_COL_0:
        case SOLITAIRE_SET_COL_1:
        case SOLITAIRE_SET_COL_2:
        case SOLITAIRE_SET_COL_3:
        case SOLITAIRE_SET_COL_4:
        case SOLITAIRE_SET_COL_5:
        case SOLITAIRE_SET_COL_6:
            if (solitaire->set[SOLITAIRE_SET_SELECTED].count > 0)
            {
                bool move_cards;

                if (solitaire->set[set].count <= 0)
                {
                    move_cards = (solitaire->set[SOLITAIRE_SET_SELECTED].set[0]->name == CARD_K);
                }
                else
                {
                    card_t * tail = solitaire->set[set].set[solitaire->set[set].count - 1u];
                    card_t * head = solitaire->set[SOLITAIRE_SET_SELECTED].set[0];

                    move_cards = (card_diff(tail, head) == 1) && (tail->suit->color != head->suit->color);
                }

                if (move_cards) cardset_transfer(
                    &solitaire->set[set],
                    &solitaire->set[SOLITAIRE_SET_SELECTED]);
            }
            else if ((solitaire->previous_set == set) && (solitaire->set[set].count > 0))
            {
                solitaire->set[set].set[solitaire->set[set].count - 1u]->facedown = false;
            }
            break;
    }
}

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

    solitaire->set[SOLITAIRE_SET_SELECTED].hide_empty = true;
}

void solitaire_draw(solitaire_t * solitaire)
{
    for (int i = 0; i < countof(solitaire->set); i++)
    {
        printf("SET: %d COUNT: %ld CARDS:", i, solitaire->set[i].count);
        cardset_draw(&solitaire->set[i]);
        printf("\n");
    }
}

void solitaire_select(solitaire_t * solitaire, GLfloat x, GLfloat y, bool active)
{
    for (int i = 0; i < countof(solitaire->set); i++)
    {
        if (i == SOLITAIRE_SET_SELECTED) continue;

        int index;

        if (cardset_within_bounds(&solitaire->set[i], x, y, &index))
        {
            if (active)
            {
                set_select(solitaire, i, x, y, index);
            }
            else
            {
                set_release(solitaire, i, x, y, index);
            }

            glutPostRedisplay();
            break;
        }
    }

    if (!active)
    {
        cardset_transfer(
            &solitaire->set[solitaire->previous_set],
            &solitaire->set[SOLITAIRE_SET_SELECTED]);
        glutPostRedisplay();
    }
}

void solitaire_motion(solitaire_t * solitaire, GLfloat x, GLfloat y)
{
    if (solitaire->set[SOLITAIRE_SET_SELECTED].count != 0)
    {
        solitaire->set[SOLITAIRE_SET_SELECTED].pos[0] = x + solitaire->offset[0];
        solitaire->set[SOLITAIRE_SET_SELECTED].pos[1] = y + solitaire->offset[1];

        glutPostRedisplay();
    }
}
