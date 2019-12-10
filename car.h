#ifndef CAR
#define CAR

#include <GL/freeglut.h>
#include "general-structures.h"
#include "obstacle.h"

class Car : public Obstacle
{
    public:
    Car()
    {
        this->speedX = 15;
        this->position.x = -500;
        this->position.y = 15;
        this->position.z = 0;
        this->yVariation = 0;
        this->floorNumber = 0;
        this->speedY = 0;
        this->height = 10;
        this->width = 10;
    }

    Car(int floorNumber, int direction, int speed)
    {
        this->speedX = (direction == DIRECTION::RIGHT) ? speed : -speed;
        this->position.x = (direction == DIRECTION::RIGHT) ? -500 : 500;
        this->position.y = floorNumber * 55 + 10;
        this->position.z = 0;
        this->yVariation = 0;
        this->speedY = 0;
        this->height = 10;
        this->width = 10;
        this->floorNumber = floorNumber;
    }

    void draw(void)
    {
        glPushMatrix();
            glColor3f(0.2, 0.2, 0.2);
            glTranslatef(this->position.x, this->position.y, this->position.z);
            glutSolidCube(10);
        glPopMatrix();
    }
};

#endif // CAR