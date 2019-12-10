#ifndef SNOWMAN
#define SNOWMAN

#include <GL/freeglut.h>
#include <stdio.h>
#include "general-structures.h"

#define SNOWMAN_JUMP_FORCE 5
#define SNOWMAN_WALK_SPEED 3

class Snowman
{
public:
    float ySpeed;
    float gravity;
    int floorNumber;
    int width;
    int height;

    bool jumping;
    bool rotationEnabled;
    bool canMove;
    bool requestingAction;

    Position position;
    Position initialPosition;
    GLfloat rotation;

    //Default constructor
    Snowman()
    {
        this->rotation = 90;
        this->position.x = 0;
        this->position.y = 0;
        this->position.z = 0;
        this->initialPosition.x = 0;
        this->initialPosition.y = 0;
        this->initialPosition.z = 0;
        this->rotationEnabled = false;
        this->ySpeed = 0.0;
        this->gravity = 0.98;
        this->floorNumber = 0;
        this->canMove = true;
        this->stairId = -1;
        this->requestingAction = false;

        // For collisions
        this->width = 20;
        this->height = 70;
    }

    // Print the snowman
    void draw()
    {
        glPushMatrix();
        glTranslatef(this->position.x, this->position.y + 29, this->position.z);
        glRotatef(this->rotation, 0, 1, 0);
        this->snowman();
        glPopMatrix();
    }

    void toggleRotation()
    {
        this->rotationEnabled = !this->rotationEnabled;
    }

    void turnLeft()
    {
        this->rotation = -90;
    }

    void turnRight()
    {
        this->rotation = 90;
    }

    void animate()
    {
        if (rotationEnabled)
        {
            rotation += 5;
        }
        if (jumping)
        {
            jumpAnimation();
        }
        if (walking)
        {
            walkAnimation();
        }
    }

    void walk()
    {
        if (canMove)
        {
            walking = true;
        }
    }

    void stop()
    {
        walking = false;
    }

    void walkAnimation()
    {
        if (canMove)
        {
            if (this->rotation == -90)
            {
                this->position.x -= SNOWMAN_WALK_SPEED;
            }
            else
            {
                this->position.x += SNOWMAN_WALK_SPEED;
            }
        }
    }

    void jump()
    {
        if (!this->jumping && this->canMove)
        {
            // printf("Starting JUMP!\n");
            this->jumping = true;
            this->createBackupPosition();
            this->ySpeed = SNOWMAN_JUMP_FORCE;
        }
    }

    void jumpAnimation()
    {
        if ((this->position.y + this->ySpeed) < this->initialPosition.y)
        {
            this->ySpeed = 0;
            this->position.y = this->initialPosition.y;
            this->jumping = false;
        }
        else
        {
            this->position.y += (int)this->ySpeed;
            this->ySpeed -= this->gravity;
        }
    }

    void setFloorNumber(int floorNumber, int floorHeight)
    {
        this->position.y = floorNumber * floorHeight;
        this->floorNumber = floorNumber;
        this->createBackupPosition();
    }

    int getFloorNumber()
    {
        return this->floorNumber;
    }

    void disableMovements(int stairId)
    {
        if (this->stairId < 0)
        {
            this->canMove = false;
            this->stairId = stairId;
        }
    }

    void enableMovements(int stairId)
    {
        if (this->stairId == stairId)
        {
            this->canMove = true;
            this->stairId = -1;
        }
    }

    bool isOnStair(int stairId)
    {
        return (this->stairId == stairId);
    }

private:
    int stairId;
    bool walking;

    void createBackupPosition()
    {
        this->initialPosition.x = this->position.x;
        this->initialPosition.y = this->position.y;
        this->initialPosition.z = this->position.z;
    }

    void snowman(void)
    {
        glPushMatrix();
        glColor3f(0.8, 0.62, 0.4);
        glTranslatef(0, -2, 0);
        glutSolidCube(8);
        glPopMatrix();
        //cabeça

        glPushMatrix();
        glTranslatef(0, -4, 5);
        glutSolidCube(3);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(0, 4, 0);
        glScalef(1, 0.6, 1.1);
        glutSolidCube(9);
        glPopMatrix();

        // glPushMatrix();
        //     glColor3f(1.0, 1.0, 1.0);
        //     glutSolidSphere(5, 20, 10);
        // glPopMatrix();

        // //pescoço
        // glPushMatrix();
        //     glColor3f(1.0, 1.0, 1.0);
        //     glTranslatef(0.0, -6, 0.0);
        //     glRotatef(90, 1, 0, 0);
        //     glutSolidTorus(3, 4, 20, 20);
        // glPopMatrix();

        //corpo
        glPushMatrix();
        glColor3f(0.2, 0.2, 1.0);
        glTranslatef(0.0, -14, 0.0);
        glScalef(0.6, 1.2, 0.5);
        glutSolidSphere(10, 20, 10);
        glPopMatrix();

        glColor3f(1.0, 1.0, 1.0);
        //braço esquerdo
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-8, -11, 0.0);
        glRotatef(45, 0, 0, 1);
        glScalef(2.5, 1, 1);
        glutSolidSphere(2, 20, 10);
        glPopMatrix();

        // Braço direito
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(8, -11, 0.0);
        glRotatef(-45, 0, 0, 1);
        glScalef(2.5, 1, 1);
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
        glTranslatef(-1.2, -1, 4.5);
        glutSolidSphere(0.5, 20, 10);
        glPopMatrix();

        //olho direito
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(1.2, -1, 4.5);
        glutSolidSphere(0.5, 20, 10);
        glPopMatrix();
    }
};

// Animação vitória!
// //braço esquerdo
// glPushMatrix();
//     glColor3f(1.0, 1.0, 1.0);
//     glTranslatef(-10, -10, 0.0);
//     glRotatef(-45, 0, 0, 1);
//     glScalef(2.5, 1, 1);
//     glutSolidSphere(2, 20, 10);
// glPopMatrix();

// // Braço direito
// glPushMatrix();
//     glColor3f(1.0, 1.0, 1.0);
//     glTranslatef(10, -10, 0.0);
//     glRotatef(45, 0, 0, 1);
//     glScalef(2.5, 1, 1);
//     glutSolidSphere(2, 20, 10);
// glPopMatrix();

#endif // SNOWMAN