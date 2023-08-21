#include "deck.h"
#include <string.h>
#include <stdio.h>

static suit_t Suits[] =
{
    {
        .name = SUIT_HEARTS,
        .color = SUIT_COLOR_RED,
        .rgb = (GLfloat[]){1.0f, 0.0f, 0.0f},
    },
    {
        .name = SUIT_DIAMONDS,
        .color = SUIT_COLOR_RED,
        .rgb = (GLfloat[]){1.0f, 0.0f, 0.0f},
    },
    {
        .name = SUIT_CLUBS,
        .color = SUIT_COLOR_BLACK,
        .rgb = (GLfloat[]){0.0f, 0.0f, 0.0f},
    },
    {
        .name = SUIT_SPADES,
        .color = SUIT_COLOR_BLACK,
        .rgb = (GLfloat[]){0.0f, 0.0f, 0.0f},
    },
};

void deck_init(deck_t * deck)
{
    int index = 0;

    for (int j = 0; j < countof(Suits); j++)
    {
        for (int i = 0; i < CARD_NUM; i++)
        {
            card_init(&deck->card[index], &Suits[j], i);
            cardset_push(&deck->set, &deck->card[index]);
            index++;
        }
    }

    cardset_shuffle(&deck->set);

    deck->selected = NULL;
}

void deck_select_card(deck_t * deck, GLfloat x, GLfloat y)
{
    for (int i = deck->set.count - 1; i >= 0; i--)
    {
        card_t * card = deck->set.set[i];

        if (card_within_bounds(card, x, y))
        {
            deck->selected = card;
            deck->offset[0] = x - card->pos[0];
            deck->offset[1] = y - card->pos[1];

            cardset_push(&deck->set, cardset_remove(&deck->set, i));
            glutPostRedisplay();
            break;
        }
    }
}

void deck_move_card(deck_t * deck, GLfloat x, GLfloat y)
{
    if (deck->selected != NULL)
    {
        deck->selected->pos[0] = x - deck->offset[0];
        deck->selected->pos[1] = y - deck->offset[1];

        glutPostRedisplay();
    }
}

void deck_draw(deck_t * deck)
{
    for (int i = 0; i < deck->set.count; i++)
    {
        card_draw(deck->set.set[i]);
    }
}
