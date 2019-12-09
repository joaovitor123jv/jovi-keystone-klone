#ifndef SNOWMAN
#define SNOWMAN

#include<GL/freeglut.h>
#include "general-structures.h"

class Snowman
{
    public:
    Position position;
    GLfloat rotation;
    bool rotationEnabled;

    //Default constructor
    Snowman()
    {
        this->rotation = 0;
        this->position.x = 0;
        this->position.y = 0;
        this->position.z = 0;
        this->rotationEnabled = false;
    }

    // Print the snowman
    void draw()
    {
        glPushMatrix();
            glTranslatef(10 + this->position.x, -18 + this->position.y, 0.0 + this->position.z);
            glRotatef(this->rotation, 0, 1, 0);
            this->snowman();
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
            this->rotation += 5;
        }
    }

    private:
    void snowman(void)
    {
        //cabeça
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glutSolidSphere(5, 20, 10);
        glPopMatrix();

        //pescoço
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(0.0, -6, 0.0);
            glRotatef(90, 1, 0, 0);
            glutSolidTorus(3, 4, 20, 20);
        glPopMatrix();

        //corpo
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(0.0, -16, 0.0);
            glScalef(1, 1.2, 1.0);
            glutSolidSphere(10, 20, 10);
        glPopMatrix();

        //braço esquerdo
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(-10, -10, 0.0);
            glScalef(2, 1, 1);
            glutSolidSphere(2, 20, 10);
        glPopMatrix();

        // Braço direito
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(10, -10, 0.0);
            glScalef(2, 1, 1);
            glutSolidSphere(2, 20, 10);
        glPopMatrix();

        //perna direita
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(6, -25, 0.0);
            glScalef(1, 2, 1);
            glutSolidSphere(2, 20, 10);
        glPopMatrix();

        //perna esquerda
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(-6, -25, 0.0);
            glScalef(1, 2, 1);
            glutSolidSphere(2, 20, 10);
        glPopMatrix();

        //olho esquerdo
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslatef(-1.2, 0.8, 5.2);
            glutSolidSphere(0.5, 20, 10);
        glPopMatrix();

        //olho direito
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslatef(1.2, 0.8, 5.2);
            glutSolidSphere(0.5, 20, 10);
        glPopMatrix();
    }
};

#endif // SNOWMAN