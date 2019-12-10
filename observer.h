#ifndef OBSERVER
#define OBSERVER

#include <GL/freeglut.h>
#include "general-structures.h"
#include "snowman.h"

class Observer
{
    public:
    Rotation rotation;
    Rotation initialRotation;

    Position position;
    Position initialPosition;

    Observer()
    {
        this->rotation.x = 10;
        this->rotation.y = 180;
        this->rotation.z = 0;
        this->initialRotation.x = 0;
        this->initialRotation.y = 0;
        this->initialRotation.z = 0;

        this->position.x = 0;
        this->position.y = 100;
        this->position.z = 350;
        this->initialPosition.x = 0;
        this->initialPosition.y = 0;
        this->initialPosition.z = 0;
    }

    void rememberValues(void)
    {
        this->initialRotation.x = this->rotation.x;
        this->initialRotation.y = this->rotation.y;

        this->initialPosition.x = this->position.x;
        this->initialPosition.y = this->position.y;
        this->initialPosition.z = this->position.z;
    }

    void follow(Snowman *snowman)
    {
        this->position.x = -snowman->position.x;
    }

    private:
};

#endif // OBSERVER