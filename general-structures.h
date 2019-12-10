#ifndef GENERAL_STRUCTURES
#define GENERAL_STRUCTURES

typedef struct 
{
    int x;
    int y;
    int z;
} Position;

typedef Position Rotation;

namespace DIRECTION
{
    enum { LEFT, RIGHT };
}

#endif // GENERAL_STRUCTURES