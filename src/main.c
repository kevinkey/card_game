#include <GL/freeglut.h>
#include <stdio.h>

//#include "deck/deck.h"

static void RenderSceneCB(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(-0.75f,0.75f, 0.75f, -0.75f);

    glutSwapBuffers();
}


int main(int argc, char ** argv)
{
    //deck_t deck;

    //deck_init(&deck);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");
    glutDisplayFunc(RenderSceneCB);
    glClearColor(0.0f, 0.5f, 0.0f, 0.0f);
    glutMainLoop();

    return 0;
}