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
    if (card == NULL) return;

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

    if (cardset->count != 0)
    {
        for (int i = 0; i < cardset->count; i++)
        {
            printf(" %c%c", card_text(cardset->set[i]), suit_text(cardset->set[i]->suit));
            cardset->set[i]->pos[0] = pos[0];
            cardset->set[i]->pos[1] = pos[1];
            card_draw(cardset->set[i]);

            pos[0] += cardset->offset[0];
            pos[1] += cardset->offset[1];
        }
    }
    else if (!cardset->hide_empty)
    {
        GLfloat tl[2] = {pos[0], pos[1]};
        GLfloat br[2] = {pos[0] + Card_Size[0], pos[1] - Card_Size[1]};

        glBegin(GL_QUADS);
        {
            glColor3f(0.0f, 0.45f, 0.0f);
            glVertex2f(tl[0], tl[1]);
            glColor3f(0.0f, 0.4f, 0.0f);
            glVertex2f(br[0], tl[1]);
            glColor3f(0.0f, 0.4f, 0.0f);
            glVertex2f(br[0], br[1]);
            glColor3f(0.0f, 0.4f, 0.0f);
            glVertex2f(tl[0], br[1]);
        }
        glEnd();

        glColor3f(0.0f, 0.3f, 0.0f);
        glBegin(GL_LINE_LOOP);
        {
            glVertex2f(tl[0], tl[1]);
            glVertex2f(tl[0], br[1]);
            glVertex2f(br[0], br[1]);
            glVertex2f(br[0], tl[1]);
        }
        glEnd();
    }
}

bool cardset_within_bounds(cardset_t * cardset, GLfloat x, GLfloat y, int * index)
{
    if (cardset->count != 0)
    {
        for (int i = cardset->count - 1; i >= 0; i--)
        {
            if (card_within_bounds(cardset->set[i], x, y))
            {
                *index = i;
                return true;
            }
        }

        return false;
    }
    else if (!cardset->hide_empty)
    {
        if (x < cardset->pos[0]) return false;
        if (x > (cardset->pos[0] + Card_Size[0])) return false;
        if (y > cardset->pos[1]) return false;
        if (y < (cardset->pos[1] - Card_Size[1])) return false;

        *index = 0;

        return true;
    }
}
