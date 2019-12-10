#ifndef SCENARIO
#define SCENARIO

#include <GL/freeglut.h>
#include <vector>
#include "stair.h"
#include "snowman.h"

class Scenario
{
    public:
    std::vector<Stair> stairs;

    Scenario() 
    {
        floorHeight = 55;

        stairs.push_back(Stair(0, 350, DIRECTION::RIGHT));
        stairs.push_back(Stair(1, -350, DIRECTION::LEFT));
        stairs.push_back(Stair(2, 350, DIRECTION::RIGHT));
    }

    void draw(void)
    {
        drawBackground();
        drawPlatform(0);
        drawPlatform(1);
        drawPlatform(2);
        drawPlatform(3);
        
        drawLeftWall();
        drawRightWall();

        drawTable(0, -50);
        drawTable(0, 50);
        drawTable(0, 290);
        drawTable(1, -100);
        drawTable(1, -20);
        drawTable(1, 280);
        drawTable(2, 0);
        drawTable(2, 100);
        drawTable(2, -100);

        for(unsigned int i=0; i < stairs.size(); i++)
        {
            stairs.at(i).draw();
        }
    }

    void animate(Snowman *snowman)
    {
        for(unsigned int i=0; i < stairs.size(); i++)
        {
            stairs.at(i).animate(snowman);
        }
    }

    void interact(Snowman *snowman)
    {
        for(unsigned int i=0; i < stairs.size(); i++)
        {
            stairs.at(i).interact(snowman);
        }
    }

    private:
    int floorHeight;

    void drawLeftWall()
    {
        glColor3f(0.0, 0.7, 0.00);
        glBegin(GL_POLYGON);
        glVertex3f(-450, 0, -20);
        glVertex3f(-450, 0, 20);
        glVertex3f(-450, 230, 20);
        glVertex3f(-450, 230, -20);
        glEnd();
    }

    void drawRightWall()
    {
        glColor3f(0.0, 0.7, 0.00);
        glBegin(GL_POLYGON);
        glVertex3f(450, 0, -20);
        glVertex3f(450, 0, 20);
        glVertex3f(450, 230, 20);
        glVertex3f(450, 230, -20);
        glEnd();
    }

    void drawPlatform(int floorNumber)
    {
        glPushMatrix();
            glTranslatef(0.0f, floorHeight * floorNumber, 0.0f);
            // Chão
            glBegin(GL_POLYGON);
            glColor3f(0.81, 0.85, 0.06);
            glVertex3f(-450, 0, -20);
            glVertex3f(-450, 0, 20);
            glVertex3f(450, 0, 20);
            glVertex3f(450, 0, -20);
            glEnd();

            // Teto da plataforma de baixo
            glBegin(GL_POLYGON);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-450, -5, -20);
            glVertex3f(-450, -5, 20);
            glVertex3f(450, -5, 20);
            glVertex3f(450, -5, -20);
            glEnd();

            glColor3f(0.68, 0.72, 0.05);
            // Lateral da frente
            glBegin(GL_POLYGON);
                glVertex3f( -450, 0, -20);
                glVertex3f( -450, -5, -20);
                glVertex3f( 450, -5, -20);
                glVertex3f( 450, 0, -20);
            glEnd();
            // Lateral do fundo
            glBegin(GL_POLYGON);
                glVertex3f( -450, 0, 20);
                glVertex3f( -450, -5, 20);
                glVertex3f( 450, -5, 20);
                glVertex3f( 450, 0, 20);
            glEnd();
        // glutSolidCube(300);
        glPopMatrix();
    }

    void drawBackground(void)
    {
        // Parede
        glBegin(GL_POLYGON);
        glColor3f(0.0, 0.8, 0.00);
        glVertex3f(-450, 0, -20);
        glVertex3f(-450, 230, -20);
        glVertex3f(450, 230, -20);
        glVertex3f(450, 0, -20);
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