#ifndef STAIR
#define STAIR

#include <GL/freeglut.h>
#include "general-structures.h"

// Fix height
// Fix degree size
class Stair
{
    public:
    Position position;
    float animationStep;

    Stair()
    {
        floorHeight = 55;
        amountOfSteps = 10;
        position.x = 0;
        position.y = 0;
        position.z = 0;
        animationStep = 0;
    }

    Stair(int floorNumber, int xPosition)
    {
        floorHeight = 55;
        amountOfSteps = 10;
        position.y = floorHeight * floorNumber;
        this->position.x = xPosition;
        this->position.y = (floorNumber * floorHeight) - 2;
        this->position.z = 0;
        animationStep = 0;
    }

    void draw(void)
    {
        drawStairSteps();
    }

    void animate(void)
    {
        if(animationStep > (floorHeight / amountOfSteps))
        {
            animationStep = 0.1;
        }
        else
        {
            animationStep += 0.2;
        }
    }

    private:
    int floorHeight;
    int amountOfSteps;

    void drawStairSteps(void)
    {
        float stepSize = floorHeight / amountOfSteps;

        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
            glTranslatef(position.x + animationStep, position.y + animationStep, position.z);
            glScalef(1, 1, 4.2);
            for(float counter = 0; counter < floorHeight; counter += stepSize)
            {
                glPushMatrix();
                    glTranslatef(counter, counter, 0);
                    glutSolidCube(stepSize);
                glPopMatrix();
            }
        glPopMatrix();
    }

    void drawStairHandRail(void)
    {
        // Currently does nothing
    }
};

#endif // STAIR