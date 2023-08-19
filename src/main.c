#include "type.h"
#include "solitaire.h"

solitaire_t solitaire;

static void RenderSceneCB(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    solitaire_draw(&solitaire);
    glutSwapBuffers();
}

static void MouseFunc(int button, int state, int x, int y)
{
    printf("Mouse: %d %d (%d, %d)\n", button, state, x , y);

    GLfloat fx = (2.0f * (GLfloat)x / (GLfloat)glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    GLfloat fy = -(2.0f * (GLfloat) y / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) - 1.0f);

    switch (button)
    {
        default:
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                deck_select_card(&solitaire.deck, fx, fy);
            }
            else
            {
                solitaire.deck.selected = NULL;
            }
            break;

        case GLUT_MIDDLE_BUTTON:

            break;

        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                deck_select_card(&solitaire.deck, fx, fy);
            }
            else
            {
                if (solitaire.deck.selected != NULL)
                {
                    solitaire.deck.selected->facedown = !solitaire.deck.selected->facedown;
                    glutPostRedisplay();
                }
                solitaire.deck.selected = NULL;
            }
            break;
    }
}

static void MotionFunc(int x, int y)
{
    GLfloat fx = (2.0f * (GLfloat)x / (GLfloat)glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    GLfloat fy = -(2.0f * (GLfloat) y / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) - 1.0f);

    deck_move_card(&solitaire.deck, fx, fy);

    printf("Motion (%f, %f)\n", fx, fy);
}

int main(int argc, char ** argv)
{
    srand(time(NULL));

    solitaire_init(&solitaire);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");
    glutDisplayFunc(RenderSceneCB);
    glutMouseFunc(MouseFunc);
    glutMotionFunc(MotionFunc);
    glClearColor(0.0f, 0.5f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}