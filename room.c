#include "room.h"
#include "string.h"


//return the room towards direction if it exits otherwise NULL;
Room* getRoom_Dir(Room* r, EDirection dir)
{
    char* direc = direction[dir];
    Room* ret = NULL;

    if(direc == NULL)
    {
        return ret;
    }
    else if(strcmp(direc, "NORTH") == 0)
    {
        if(r->north != NULL)
            ret = r->north;
    }
    else if(strcmp(direc, "SOUTH") == 0)
    {
        if(r->south != NULL)
            ret = r->south;
    }
    else if(strcmp(direc, "EAST") == 0)
    {
        if(r->east != NULL)
            ret = r->east;
    }
    else if(strcmp(direc, "WEST") == 0)
    {
        if(r->west != NULL)
            ret = r->west;
    }

    return ret;
}