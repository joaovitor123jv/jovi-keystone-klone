#include<GL/freeglut.h>
#include "general-structures.h"

class Sun
{
    public:
    Position position;
    GLfloat rotation;
    bool rotationEnabled;

    //Default constructor
    Sun()
    {
        this->rotation = 0;
        this->position.x = -70;
        this->position.y = 80;
        this->position.z = -100;
        this->rotationEnabled = true;
    }

    // Print the snowman
    void draw()
    {
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glTranslatef(this->position.x, this->position.y, this->position.z);
            glRotatef(this->rotation, 0, 0, 1);
            glutSolidSphere(15, 15, 10);
        glPopMatrix();
    }

    void toggleRotation()
    {
        this->rotationEnabled = ! this->rotationEnabled;
    }

    void animate()
    {
        if(this->rotationEnabled)
        {
            if(this->rotation + 1 > 360.0f)
            {
                this->rotation = 0;
            }

            this->rotation += 10;
        }
    }
};
