#include "cardset.h"

typedef struct
{
    card_t * card;
    int random;
} sort_t;

static int compare(const void * e1, const void * e2)
{
    int f = ((sort_t *)e1)->random;
    int s = ((sort_t *)e2)->random;
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void cardset_init(cardset_t * cardset)
{
    cardset->count = 0;
}

void cardset_push(cardset_t * cardset, card_t * card)
{
    if (cardset->count == 0)
    {
        cardset->set = malloc(sizeof(card));
    }
    else
    {
        cardset->set = realloc(cardset->set, (cardset->count + 1) * sizeof(card_t *));
    }

    cardset->set[cardset->count] = card;
    cardset->count++;
}

card_t * cardset_remove(cardset_t * cardset, int index)
{
    if ((index < 0) || (index >= cardset->count)) return NULL;

    card_t * card = cardset->set[index];

    cardset->count--;
    if (cardset->count == 0)
    {
        free(cardset->set);
    }
    else
    {
        for (int i = index; i < cardset->count; i++)
        {
            cardset->set[i] = cardset->set[i + 1];
        }
    }

    return card;
}

card_t * cardset_pop(cardset_t * cardset)
{
    return cardset_remove(cardset, cardset->count - 1);
}

void cardset_shuffle(cardset_t * cardset)
{
    if (cardset->count <= 1) return;

    sort_t * sort = malloc(sizeof(sort_t) * cardset->count);

    for (int i = 0; i < cardset->count; i++)
    {
        sort[i].card = cardset->set[i];
        sort[i].random = rand();
    }

    qsort(sort, cardset->count, sizeof(sort_t), compare);

    for (int i = 0; i < cardset->count; i++)
    {
        cardset->set[i] = sort[i].card;
    }

    free(sort);
}

void cardset_draw(cardset_t * cardset)
{
    GLfloat pos[2] = {cardset->pos[0], cardset->pos[1]};

    for (int i = 0; i < cardset->count; i++)
    {
        cardset->set[i]->pos[0] = pos[0];
        cardset->set[i]->pos[1] = pos[1];
        card_draw(cardset->set[i]);

        pos[0] += cardset->offset[0];
        pos[1] += cardset->offset[1];
    }
}
