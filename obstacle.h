#ifndef OBSTABLE
#define OBSTACLE

#include "general-structures.h"
#include "snowman.h"

static unsigned int OBSTACLE_ID = 0;

class Obstacle
{
    public:
    int speedX;
    int speedY;
    int width;
    int height;
    int floorNumber;
    int yVariation;
    Position position;

    Obstacle()
    {

    }

    void animate()
    {
        position.x += speedX;
        if(yVariation != 0)
        {
            if(yVariated < yVariation)
            {
                position.y += speedY * currentDirection;
                yVariated += speedY;
            }
            else
            {
                currentDirection = -currentDirection;
                yVariated = 0;
            }
        }
    }

    bool hasCollided(Snowman *snowman)
    {
        if(this->floorNumber == snowman->floorNumber)
            if((snowman->position.x + snowman->width/2) >= (position.x - width/2))
                if((snowman->position.x - snowman->width/2) <= (position.x + width/2))
                    if((snowman->position.y + snowman->height/2) <= (position.y - height/2))
                        if((snowman->position.y - snowman->height/2) >= (position.y + height/2))
                            return true;

        return false;
    }

    private:
    static int maxX;
    static int minX;
    int yVariated;
    short int currentDirection = 1;

    void timeBomb()
    {
        if(this->position.x > maxX || this->position.x < minX)
        {
            delete this;
        }
    }
};

#endif