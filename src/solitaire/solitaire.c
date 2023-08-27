#include "solitaire.h"

static bool move_home(cardset_t * home, card_t * card)
{
    if (card == NULL) return false;

    card_t * tail = cardset_tail(home);
    bool move_card;

    if (tail == NULL)
    {
        move_card = (card->name == CARD_A);
    }
    else
    {
        move_card = (card_diff(tail, card) == -1) && (tail->suit->name == card->suit->name);
    }

    return move_card;
}

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
            cardset_push(
                &solitaire->set[SOLITAIRE_SET_SELECTED],
                cardset_pop(&solitaire->set[set]));
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
            if (move_home(&solitaire->set[set], cardset_head(&solitaire->set[SOLITAIRE_SET_SELECTED])))
                cardset_transfer(
                    &solitaire->set[set],
                    &solitaire->set[SOLITAIRE_SET_SELECTED]);
            break;
        case SOLITAIRE_SET_COL_0:
        case SOLITAIRE_SET_COL_1:
        case SOLITAIRE_SET_COL_2:
        case SOLITAIRE_SET_COL_3:
        case SOLITAIRE_SET_COL_4:
        case SOLITAIRE_SET_COL_5:
        case SOLITAIRE_SET_COL_6:
        {
            card_t * head = cardset_head(&solitaire->set[SOLITAIRE_SET_SELECTED]);
            card_t * tail = cardset_tail(&solitaire->set[set]);

            if (head != NULL)
            {
                bool move_cards;

                if (tail == NULL)
                {
                    move_cards = (head->name == CARD_K);
                }
                else
                {
                    move_cards = (card_diff(tail, head) == 1) && (tail->suit->color != head->suit->color);
                }

                if (move_cards) cardset_transfer(
                    &solitaire->set[set],
                    &solitaire->set[SOLITAIRE_SET_SELECTED]);
            }
            else if ((solitaire->previous_set == set) && (tail != NULL))
            {
                tail->facedown = false;
            }
            break;
        }
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

        solitaire->set[i].pos[1] = Card_Size[1] - 0.05f;
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

    time(&solitaire->start_time);
}

void solitaire_draw(solitaire_t * solitaire)
{
    glColor3f(0.0f, 0.4f, 0.0f);
    glRectf(-1.0f, -0.9f, 1.0f, -1.0f);

    time_t now;

    time(&now);

    int elapsed = (int)difftime(now, solitaire->start_time);
    char seconds[16];
    int length = snprintf(seconds, sizeof(seconds), "%d", elapsed);

    glColor3f(0.0f, 0.2f, 0.0f);
    glRasterPos2f(0.005f, -0.975f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, seconds);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(0.0f, -0.97f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, seconds);

    for (int set = 0; set < countof(solitaire->set); set++)
    {
        switch(set)
        {
            case SOLITAIRE_SET_COL_0:
            case SOLITAIRE_SET_COL_1:
            case SOLITAIRE_SET_COL_2:
            case SOLITAIRE_SET_COL_3:
            case SOLITAIRE_SET_COL_4:
            case SOLITAIRE_SET_COL_5:
            case SOLITAIRE_SET_COL_6:
            {
                GLfloat offset;

                offset = (2.0f - (2.0f * Card_Size[1]) - 0.2f)
                    / ((GLfloat)max(solitaire->set[set].count, 1));
                offset = max(-0.1f, -offset);

                solitaire->set[set].offset[1] = offset;
                break;
            }
        }

        cardset_draw(&solitaire->set[set]);
    }
}

void solitaire_select(solitaire_t * solitaire, GLfloat x, GLfloat y, bool active)
{
    GLfloat pos[2] = {x, y};

    if (!active)
    {
        card_t * head = cardset_head(&solitaire->set[SOLITAIRE_SET_SELECTED]);

        if (head != NULL)
        {
            pos[0] = head->pos[0] + (Card_Size[0] / 2.0f);
            pos[1] = head->pos[1] - (Card_Size[1] / 2.0f);
        }
    }

    for (int i = 0; i < countof(solitaire->set); i++)
    {
        if (i == SOLITAIRE_SET_SELECTED) continue;

        int index;

        if (cardset_within_bounds(&solitaire->set[i], pos[0], pos[1], &index))
        {
            if (active)
            {
                set_select(solitaire, i, pos[0], pos[1], index);
            }
            else
            {
                set_release(solitaire, i, pos[0], pos[1], index);
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

void solitaire_auto_home(solitaire_t * solitaire)
{
    bool any_moved = false;
    bool moved;

    do
    {
        moved = false;

        for (int set = 0; set < SOLITAIRE_SET_NUM; set++)
        {
            switch (set)
            {
                case SOLITAIRE_SET_DISCARD:
                case SOLITAIRE_SET_COL_0:
                case SOLITAIRE_SET_COL_1:
                case SOLITAIRE_SET_COL_2:
                case SOLITAIRE_SET_COL_3:
                case SOLITAIRE_SET_COL_4:
                case SOLITAIRE_SET_COL_5:
                case SOLITAIRE_SET_COL_6:
                {
                    card_t * tail = cardset_tail(&solitaire->set[set]);

                    if (tail != NULL)
                    {
                        if (!tail->facedown)
                        {
                            for (int home = SOLITAIRE_SET_HOME_0; home <= SOLITAIRE_SET_HOME_3; home++)
                            {
                                if (move_home(&solitaire->set[home], tail))
                                {
                                    moved = true;
                                    any_moved = true;
                                    cardset_push(&solitaire->set[home], cardset_pop(&solitaire->set[set]));
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (moved);

    if (any_moved) glutPostRedisplay();
}