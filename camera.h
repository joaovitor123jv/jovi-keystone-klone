#ifndef CAMERA
#define CAMERA

#include <GL/freeglut.h>
#include "general-structures.h"
#include "snowman.h"

class Camera
{
    public:
    Position position2D;
    Rotation rotation;
    int topIs;
    GLfloat angle;
    GLfloat aspect;

    Camera()
    {
        this->position2D.x = 0;
        this->position2D.y = 0;
        this->position2D.z = 10;
        this->angle = 45;
        this->aspect = 0;
    }

    void look(void)
    {
        gluLookAt(
            this->position2D.x, this->position2D.y, this->position2D.x,
            this->position2D.x, this->position2D.y, this->position2D.z,
            0, 1, 0);
    }

    void updateAspect(GLfloat width, GLfloat height)
    {
        this->aspect = width / height;
    }

    void follow(Snowman *snowman)
    {
        this->position2D.x = -snowman->position.x;
    }
};

#endif // CAMERA