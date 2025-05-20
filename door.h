#ifndef DOOR_H
#define DOOR_H

#include "stdint.h"

struct Room;

typedef struct Door
{
    char* name;
    char* desc;

    struct Room* room_to;
    struct Room* room_from;

    uint8_t open;
    
} Door;

Door* doorInit(char* name, char* desc, struct Room* connect_to, struct Room* connect_from, uint8_t open);

#endif