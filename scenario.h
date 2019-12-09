#ifndef SCENARIO
#define SCENARIO

#include<GL/freeglut.h>

class Scenario
{
    public:
    Scenario() 
    {
        floorHeight = 55;
    }

    void draw(void)
    {
        drawBackground();
        drawPlatform(0);
        drawPlatform(1);
        drawPlatform(2);

        drawTable(0, 0);
        drawTable(1, 0);
        drawTable(2, 0);
    }

    private:
    int floorHeight;

    void drawPlatform(int floorNumber)
    {
        glPushMatrix();
            glTranslatef(0.0f, floorHeight * floorNumber, 0.0f);
            // Chão
            glBegin(GL_POLYGON);
            glColor3f(0.81, 0.85, 0.06);
            glVertex3f(-300, 0, -20);
            glVertex3f(-300, 0, 20);
            glVertex3f(300, 0, 20);
            glVertex3f(300, 0, -20);
            glEnd();

            // Teto da plataforma de baixo
            glBegin(GL_POLYGON);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-300, -5, -20);
            glVertex3f(-300, -5, 20);
            glVertex3f(300, -5, 20);
            glVertex3f(300, -5, -20);
            glEnd();

            glColor3f(0.68, 0.72, 0.05);
            // Lateral da frente
            glBegin(GL_POLYGON);
                glVertex3f( -300, 0, -20);
                glVertex3f( -300, -5, -20);
                glVertex3f( 300, -5, -20);
                glVertex3f( 300, 0, -20);
            glEnd();
            // Lateral do fundo
            glBegin(GL_POLYGON);
                glVertex3f( -300, 0, 20);
                glVertex3f( -300, -5, 20);
                glVertex3f( 300, -5, 20);
                glVertex3f( 300, 0, 20);
            glEnd();
        // glutSolidCube(300);
        glPopMatrix();
    }

    void drawBackground(void)
    {
        // Parede
        glBegin(GL_POLYGON);
        glColor3f(0.0, 0.8, 0.00);
        glVertex3f(-300, 0, -20);
        glVertex3f(-300, 130, -20);
        glVertex3f(300, 130, -20);
        glVertex3f(300, 0, -20);
        glEnd();
    }

    void drawTable(int floorNumber, int xPosition)
    {
        // Table body
        glPushMatrix();
            glTranslatef(xPosition, floorHeight * floorNumber + 6, -15);
            glColor3f(0.05, 0.05, 1.0);
            glScalef(1.0, 0.3, 0.1);
            glutSolidCube(50);
        glPopMatrix();

        // Table top
        glPushMatrix();
            glTranslatef(xPosition, floorHeight * floorNumber + 14, -15);
            glColor3f(0.1, 0.1, 1.0);
            glScalef(1.1, 0.03, 0.15);
            glutSolidCube(50);
        glPopMatrix();
    }
};

#endif // SCENARIO