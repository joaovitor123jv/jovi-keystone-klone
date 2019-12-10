#ifndef BALL
#define BALL

#include <GL/freeglut.h>
#include "general-structures.h"
#include "obstacle.h"

class Ball : public Obstacle
{
    public:
    Ball()
    {
        this->speedX = 5;
        this->position.x = -300;
        this->position.y = 75;
        this->position.z = 0;
        this->yVariation = 16;
        this->speedY = 1;
        this->height = 10;
        this->width = 10;
    }

    Ball(int floorNumber, int direction, int speed)
    {
        this->speedX = (direction == DIRECTION::RIGHT) ? speed : -speed;
        this->position.x = (direction == DIRECTION::RIGHT) ? -300 : 300;
        this->position.y = floorNumber * 55 + 10;
        this->position.z = 0;
        this->yVariation = 30;
        this->speedY = 1;
        this->height = 10;
        this->width = 10;
    }

    void draw(void)
    {
        glPushMatrix();
            glColor3f(0.7, 0.2, 0.1);
            glTranslatef(this->position.x, this->position.y, this->position.z);
            glutSolidSphere(5, 20, 20);
        glPopMatrix();
    }
};

#endif // BALL