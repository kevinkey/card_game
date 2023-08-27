#include "card.h"
#include <ft2build.h>

GLfloat Card_Size[2];

void card_init(card_t * card, suit_t * suit, card_name_t name)
{
    card->suit = suit;
    card->name = name;
    card->pos[0] = 0.0f;
    card->pos[1] = 0.0f;
}

bool card_within_bounds(card_t * card, GLfloat x, GLfloat y)
{
    if (x < card->pos[0]) return false;
    if (x > (card->pos[0] + Card_Size[0])) return false;
    if (y > card->pos[1]) return false;
    if (y < (card->pos[1] - Card_Size[1])) return false;

    return true;
}

void card_draw(card_t * card)
{
    GLfloat tl[2] = {card->pos[0], card->pos[1]};
    GLfloat br[2] = {card->pos[0] + Card_Size[0], card->pos[1] - Card_Size[1]};

    GLfloat c1[3] = {0.0f, 0.1f, 0.5f};
    GLfloat c2[3] = {0.2f, 0.3f, 0.7f};

    if (!card->facedown)
    {
        c1[0] = 1.0f;
        c1[1] = 1.0f;
        c1[2] = 1.0f;
        c2[0] = 0.7f;
        c2[1] = 0.7f;
        c2[2] = 0.7f;
    }

    glBegin(GL_QUADS);
    {
        glColor3f(c1[0], c1[1], c1[2]);
        glVertex2f(tl[0], tl[1]);
        glColor3f(c1[0], c1[1], c1[2]);
        glVertex2f(br[0], tl[1]);
        glColor3f(c2[0], c2[1], c2[2]);
        glVertex2f(br[0], br[1]);
        glColor3f(c1[0], c1[1], c1[2]);
        glVertex2f(tl[0], br[1]);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    {
        glVertex2f(tl[0], tl[1]);
        glVertex2f(tl[0], br[1]);
        glVertex2f(br[0], br[1]);
        glVertex2f(br[0], tl[1]);
    }
    glEnd();

    if (!card->facedown)
    {
        glColor3f(card->suit->rgb[0], card->suit->rgb[1], card->suit->rgb[2]);
        glRasterPos2f(tl[0], tl[1] - 0.05);

        glPushMatrix();
        glTranslatef(tl[0] + 0.01f, tl[1] - 0.05f, 0.0f);
        glScalef(0.0003f, 0.0003f, 0.0003f);
        glLineWidth(2.0f);
        glutStrokeString(GLUT_STROKE_ROMAN, (char[]){card_text(card), suit_text(card->suit)});
        glLineWidth(1.0f);
	    glPopMatrix();

        //glutBitmapString(GLUT_BITMAP_HELVETICA_18, (char[]){card_text(card), suit_text(card->suit)});
    }
}

char card_text(card_t * card)
{
    static char const text[] =
    {
        'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'
    };

    return text[card->name];
}

int card_diff(card_t * card_a, card_t * card_b)
{
    return card_a->name - card_b->name;
}
