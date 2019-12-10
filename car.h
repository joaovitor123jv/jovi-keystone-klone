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
        this->position.x = -300;
        this->position.y = 15;
        this->position.z = 0;
        this->yVariation = 0;
        this->speedY = 0;
        this->height = 10;
        this->width = 10;
    }

    Car(int floorNumber, int direction, int speed)
    {
        this->speedX = speed;
        this->position.x = (direction == DIRECTION::RIGHT) ? -300 : 300;
        this->position.y = floorNumber * 55 + 15;
        this->position.z = 0;
        this->yVariation = 0;
        this->speedY = 0;
        this->height = 10;
        this->width = 10;
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