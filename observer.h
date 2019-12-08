#include <GL/freeglut.h>
#include "general-structures.h"

class Observer
{
    public:
    Rotation rotation;
    Rotation initialRotation;

    Position position;
    Position initialPosition;

    Observer()
    {
        this->rotation.x = 0;
        this->rotation.y = 0;
        this->rotation.z = 0;
        this->initialRotation.x = 0;
        this->initialRotation.y = 0;
        this->initialRotation.z = 0;

        this->position.x = 0;
        this->position.y = 0;
        this->position.z = 150;
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

    private:
};