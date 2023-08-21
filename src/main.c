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
    if (button == GLUT_LEFT_BUTTON)
    {
        GLfloat fx = (2.0f * (GLfloat)x / (GLfloat)glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
        GLfloat fy = -(2.0f * (GLfloat) y / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) - 1.0f);

        solitaire_select(&solitaire, fx, fy, state == GLUT_DOWN);
    }
}

static void MotionFunc(int x, int y)
{
    GLfloat fx = (2.0f * (GLfloat)x / (GLfloat)glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    GLfloat fy = -(2.0f * (GLfloat) y / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) - 1.0f);

    solitaire_motion(&solitaire, fx, fy);
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