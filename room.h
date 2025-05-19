#ifndef ROOM_H
#define ROOM_H

#include <stdint.h>
#include <stddef.h>

#include "door.h"
#include "object.h"

#define FOREACH_DIR(DIR) \
        DIR(NORTH)   \
        DIR(SOUTH)  \
        DIR(EAST)   \
        DIR(WEST)  \
        DIR(ERROR) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum EDirection {
    FOREACH_DIR(GENERATE_ENUM)
}EDirection;

static const char *Direction_String[] = {
    FOREACH_DIR(GENERATE_STRING)
};

static size_t Direction_Size = sizeof(Direction_String) / sizeof(Direction_String[0]);

struct Player;

typedef struct Room
{
    char* name;
    char* desc;
    
    uint8_t visited;

    Door* north;
    Door* south;
    Door* east;
    Door* west;

    ObjectContainer* inventory;

    char* (*enterRoom)();
    char* (*exitRoom)();

}Room;

Room* initRoom(char* name, char* desc);

Room* getRoom_Dir(Room* r, EDirection dir);

char* getRoomDesc(Room* r);

char* getRoomName(Room* r);

#endif