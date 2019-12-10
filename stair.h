#ifndef STAIR
#define STAIR

#include <GL/freeglut.h>
#include "general-structures.h"
#include "snowman.h"

int STAIR_ID;

class Stair
{
    public:
    Position position;
    int floorNumber;
    float animationStep;

    Stair()
    {
        floorHeight = 55;
        amountOfSteps = 10;
        position.x = 0;
        position.y = 0;
        position.z = 0;
        animationStep = 0;
        floorNumber = 0;
        id = STAIR_ID++;
        isCarryingSomething = false;
    }

    Stair(int floorNumber, int xPosition)
    {
        floorHeight = 55;
        amountOfSteps = 10;
        position.y = floorHeight * floorNumber;
        this->position.x = xPosition;
        this->floorNumber = floorNumber;
        this->position.y = floorNumber * floorHeight;
        this->position.z = 0;
        animationStep = 0;
        id = STAIR_ID++;
        isCarryingSomething = false;
    }

    void draw(void)
    {
        drawStairSteps();
    }

    void animate(Snowman *snowman)
    {
        if(isCarryingSomething)
        {
            snowman->stairUp(1);
        }

        if(animationStep > (floorHeight / amountOfSteps))
        {
            animationStep = 0.6;
        }
        else
        {
            animationStep += 0.8;
        }
    }

    void interact(Snowman *snowman)
    {
        if (snowman->canMove)
        {
            if(snowman->requestingAction)
            {
                if (isPlayerHere(snowman))
                {
                    snowman->disableMovements(this->id);
                    this->isCarryingSomething = true;
                    snowman->requestingAction = false;
                }
            }
        }
        else if (snowman->isOnStair(this->id))
        {
            if(endedTravel(snowman))
            {
                this->isCarryingSomething = false;
                snowman->enableMovements(this->id);
                snowman->setFloorNumber(this->floorNumber+1, this->floorHeight);
            }
        }
    }

    private:
    int id;
    int floorHeight;
    int amountOfSteps;
    bool isCarryingSomething;

    void drawStairSteps(void)
    {
        float stepSize = floorHeight / amountOfSteps;

        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
            glTranslatef(position.x + animationStep, position.y - 2 + animationStep, position.z);
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

    bool isPlayerHere(Snowman *snowman)
    {
        if (this->floorNumber == snowman->floorNumber) // Compares position X
        {
            if (snowman->position.x >= this->position.x)
            {
                if (snowman->position.x <= this->position.x + 5)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool endedTravel(Snowman *snowman)
    {
        return (snowman->position.y >= (this->floorNumber + 1) * this->floorHeight);
    }

    void drawStairHandRail(void)
    {
        // Currently does nothing
    }
};

#endif // STAIR