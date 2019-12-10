#ifndef CAMERA
#define CAMERA

#include <GL/freeglut.h>
#include "general-structures.h"
#include "snowman.h"

class Camera
{
    public:
    Position position;
    Rotation rotation;
    int topIs;
    GLfloat angle;
    GLfloat aspect;

    Camera()
    {
        this->position.x = 0;
        this->position.y = 0;
        this->position.z = 10;
        this->angle = 45;
        this->aspect = 0;
    }

    void look(void)
    {
        gluLookAt(
            this->position.x, this->position.y, this->position.x,
            this->position.x, this->position.y, this->position.z,
            0, 1, 0);
    }

    void updateAspect(GLfloat width, GLfloat height)
    {
        this->aspect = width / height;
    }

    void follow(Snowman *snowman)
    {
        this->position.x = -snowman->position.x;
    }
};

#endif // CAMERA