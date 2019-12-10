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

static bool focusPlayer;

#endif // GENERAL_STRUCTURES