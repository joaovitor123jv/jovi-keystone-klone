#ifndef OBSTACLE_JOVI
#define OBSTACLE_JOVI

#include "general-structures.h"
#include "snowman.h"

static unsigned int OBSTACLE_ID = 0;

class Obstacle
{
    public:
    int id;
    int speedX;
    int speedY;
    int width;
    int height;
    int floorNumber;
    int yVariation;
    bool isUseless;
    Position position;

    Obstacle()
    {
        this->id = OBSTACLE_ID++;
        this->currentDirection = 1;
        this->isUseless = false;
        this->yVariated = 1;
    }

    void animate()
    {
        position.x += speedX;
        if(yVariation != 0)
        {
            if(yVariated == yVariation || yVariated == 0)
            {
                currentDirection *= -1;
            }
            position.y += speedY * currentDirection;
            yVariated += speedY * currentDirection;
        }
        timeBomb();
    }

    virtual void draw() = 0;

    bool hasCollided(Snowman *snowman)
    {
        if(this->floorNumber == snowman->floorNumber)
        {
            if((snowman->position.x + snowman->width/2) >= (position.x - width/2))
            {
                if((snowman->position.x - snowman->width/2) <= (position.x + width/2))
                {
                    if((snowman->position.y + snowman->height) >= (position.y - height/2))
                    {
                        if((snowman->position.y + 5) <= (position.y + height/2))
                        {
                            printf("TESTER\n");
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    private:
    const static int maxX = 500;
    const static int minX = -500;
    int yVariated;
    short int currentDirection;

    void timeBomb()
    {
        if(this->position.x > maxX || this->position.x < minX)
        {
            this->isUseless = true;
        }
    }
};

#endif // OBSTACLE_JOVI