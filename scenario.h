#include<GL/freeglut.h>

void drawScenario()
{
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(0.0, -200.0, 50.0);
    glutSolidCube(300);
    glPopMatrix();
}