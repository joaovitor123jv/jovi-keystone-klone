#include <GL/freeglut.h>
#include "general-structures.h"
#include "observer.h"
#include "camera.h"
#include "snowman.h"

class ControlsManager
{
    public:
    int deltaX;
    int deltaY;
    int deltaZ;

    ControlsManager()
    {
        button = -1;
        cursorPosition.x = 0;
        cursorPosition.y = 0;
        cursorPosition.z = 0;
        rotationSensibility = 5.0;
        translationSensibility = 10.0;
        observerSensibility = 10.0;
        movementActionsPressed = 0;
        observer = NULL;
    }

    void onMouseButtonClick(int button, int state, int x, int y)
    {
        if (state == GLUT_DOWN)
        {
            this->button = button;
            cursorPosition.x = x;
            cursorPosition.y = y;
        }
        else
        {
            this->button = -1;
        }
    }

    void onMouseMotion(int x, int y)
    {
        deltaX = cursorPosition.x - x;
        deltaY = cursorPosition.y - y;
        deltaZ = cursorPosition.x - x;

        if (button == GLUT_LEFT_BUTTON)
        {
            // E modifica ângulos
            observer->rotation.x = observer->initialRotation.x - deltaY / rotationSensibility;
            observer->rotation.y = observer->initialRotation.y - deltaX / rotationSensibility;
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            observer->position.z = observer->initialPosition.z + deltaZ / observerSensibility; // E modifica distância do observador
        }
        else if (button == GLUT_MIDDLE_BUTTON)
        {
            // E modifica posições
            observer->position.x = observer->initialPosition.x - deltaX / translationSensibility;
            observer->position.y = observer->initialPosition.y - deltaY / translationSensibility;
        }
    }

    void onKeyDownEvent(unsigned char key, int x, int y)
    {
        switch (key)
        {
        case 27:
            exit(0);
            break;

        case ' ':
            snowman->requestingAction = true;
            break;

        // case 'a':
        //     camera->position.x++;
        //     break;

        // case 'z':
        //     camera->position.y--;
        //     break;

        // case 's':
        //     camera->position.y++;
        //     break;

        // case 'x':
        //     camera->position.y--;
        //     break;

        // case 'd':
        //     camera->position.z++;
        //     break;

        // case 'c':
        //     camera->position.z--;
        //     break;
        }
    }

    void onKeyUpEvent(unsigned char key, int x, int y)
    {
        switch (key)
        {
        case ' ':
            snowman->requestingAction = false;
            break;
        }
    }

    void onSpecialKeyDownEvent(int keyCode, int x, int y)
    {
        switch (keyCode)
        {
        case GLUT_KEY_HOME:
            if (camera->angle >= 10)
                camera->angle -= 5;
            break;

        case GLUT_KEY_END:
            if (camera->angle <= 150)
                camera->angle += 5;
            break;

        case GLUT_KEY_F10:
            snowman->toggleRotation();
            break;

        case GLUT_KEY_UP:
            snowman->jump();
            break;

        // case GLUT_KEY_DOWN:
        //     snowman->position.y -= 2;
        //     break;

        case GLUT_KEY_LEFT:
            snowman->turnLeft();
            snowman->walk();
            this->movementActionsPressed += 1;
            break;

        case GLUT_KEY_RIGHT:
            snowman->turnRight();
            snowman->walk();
            this->movementActionsPressed += 1;
            break;

        case GLUT_KEY_F3:
            snowman->position.z += 2;
            break;

        case GLUT_KEY_F4:
            snowman->position.z -= 2;
            break;
        }
    }

    void onSpecialKeyUpEvent(int keyCode, int x, int y)
    {
        switch (keyCode)
        {
        case GLUT_KEY_LEFT:
            this->movementActionsPressed -= 1;
            if(this->movementActionsPressed == 0)
            {
                snowman->stop();
            }
            break;

        case GLUT_KEY_RIGHT:
            this->movementActionsPressed -= 1;
            if(this->movementActionsPressed == 0)
            {
                snowman->stop();
            }
            break;
        }
    }

    void setObserver(Observer *observer)
    {
        this->observer = observer;
    }

    void setCamera(Camera *camera)
    {
        this->camera = camera;
    }

    void setSnowman(Snowman *snowman)
    {
        this->snowman = snowman;
    }

    private:
    int button;
    short int movementActionsPressed;
    float rotationSensibility;
    float translationSensibility;
    float observerSensibility;
    Position cursorPosition;

    Observer *observer;
    Camera *camera;
    Snowman *snowman;
};