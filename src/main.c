#include "type.h"
#include "solitaire.h"

FT_Library FT;
solitaire_t Solitaire;

static void RenderSceneCB(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    solitaire_draw(&Solitaire);
    glutSwapBuffers();
}

static void MouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        GLfloat fx = (2.0f * (GLfloat)x / (GLfloat)glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
        GLfloat fy = -(2.0f * (GLfloat) y / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) - 1.0f);

        solitaire_select(&Solitaire, fx, fy, state == GLUT_DOWN);
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_UP) solitaire_auto_home(&Solitaire);
    }
}

static void MotionFunc(int x, int y)
{
    GLfloat fx = (2.0f * (GLfloat)x / (GLfloat)glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    GLfloat fy = -(2.0f * (GLfloat) y / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) - 1.0f);

    solitaire_motion(&Solitaire, fx, fy);
}

static void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000u, TimerFunc, 0);
}

int main(int argc, char ** argv)
{
    srand(time(NULL));

    if (FT_Init_FreeType(&FT))
    {
        printf("Failed to load freetype\n");
    }

    solitaire_init(&Solitaire);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");
    glutDisplayFunc(RenderSceneCB);
    glutMouseFunc(MouseFunc);
    glutMotionFunc(MotionFunc);
    glutTimerFunc(1000u, TimerFunc, 0);
    glClearColor(0.0f, 0.5f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}