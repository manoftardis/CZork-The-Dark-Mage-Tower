#ifndef DOOR_H
#define DOOR_H

#include "room.h"

typedef struct Door
{
    char* name;
    char* desc;

    Room* room_to;
    Room* room_from;

    uint8_t open;
    
} Door;

Door* doorInit(char* name, char* desc, Room* connect_to, Room* connect_from, uint8_t open);

#endif