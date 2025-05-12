#ifndef ROOM_H
#define ROOM_H

#include "object.h"
#include <stdint.h>

struct Player;

typedef struct Room
{
    char* name;
    char* desc;
    
    uint8_t visited;

    Room* connected;

    void (*enterFunc)(struct Player* p);
    void (*exitFunc)(char* dir);

}Room;


#endif