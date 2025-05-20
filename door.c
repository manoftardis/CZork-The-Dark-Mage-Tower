#include <stdlib.h>
#include "door.h"


Door *doorInit(char *name, char *desc, struct Room *connect_to, struct Room *connect_from, uint8_t open)
{
    Door* ret = malloc(sizeof(*ret));
    ret->name = name;
    ret->desc = desc;
    ret->room_to = connect_to;
    ret->room_from = connect_from;
    ret->open = open;
    return ret;
}