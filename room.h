#ifndef ROOM_H
#define ROOM_H

#include "object.h"
#include <stdint.h>

struct Player;

typedef enum EDirection
{
    NORTH,
    SOUTH,
    EAST,
    WEST,

}EDirection;

const char* direction[] = {"NORTH", "SOUTH", "EAST", "WEST", NULL};

typedef struct Room
{
    char* name;
    char* desc;
    
    uint8_t visited;

    //one or multiple ones???
    Room* north;
    Room* south;
    Room* east;
    Room* west;

    void (*enterFunc)(struct Player* p);
    void (*exitFunc)(char* dir);

}Room;

Room* getRoom_Dir(Room* r, EDirection dir);


#endif