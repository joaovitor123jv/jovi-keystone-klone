#ifndef CAMERA
#define CAMERA

#include <GL/freeglut.h>
#include "general-structures.h"

namespace CAMERA
{
    enum
    {
        TOP_IS_X,
        TOP_IS_Y,
        TOP_IS_Z
    };
}

class Camera
{
    public:
    Position position;
    Rotation rotation;
    int topIs;
    GLfloat angle;
    GLfloat aspect;

    // Defaults to TOP_IS_Y
    Camera()
    {
        this->topIs = CAMERA::TOP_IS_Y;
        this->position.x = 0;
        this->position.y = 0;
        this->position.z = 10;
        this->angle = 45;
        this->aspect = 0;
    }

    void look(void)
    {
        switch (this->topIs)
        {
        case CAMERA::TOP_IS_X:
            gluLookAt(
                this->position.x, this->position.y, this->position.x,
                this->position.x, this->position.y, this->position.z,
                1, 0, 0);
            break;
        
        case CAMERA::TOP_IS_Z:
            gluLookAt(
                this->position.x, this->position.y, this->position.x,
                this->position.x, this->position.y, this->position.z,
                0, 0, 1);
            break;

        case CAMERA::TOP_IS_Y:
        default:
            gluLookAt(
                this->position.x, this->position.y, this->position.x,
                this->position.x, this->position.y, this->position.z,
                0, 1, 0);
            break;
        }
    }

    void updateAspect(GLfloat width, GLfloat height)
    {
        this->aspect = width / height;
    }
};

#endif // CAMERA