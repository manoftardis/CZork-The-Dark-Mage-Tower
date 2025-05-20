#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "room.h"

Room *initRoom(char *name, char *desc)
{
    Room* ret = malloc(sizeof(Room));
    ret->name = name;
    ret->desc = desc;
    ret->visited = 0;
    ret->north = NULL;
    ret->south = NULL;
    ret->east = NULL;
    ret->west = NULL;

    ret->inventory = malloc(sizeof(ObjectContainer));


    return ret;
}

// return the room towards direction if it exits otherwise NULL;
Room* getRoom_Dir(Room* r, EDirection dir)
{
    const char* direc = Direction_String[dir];
    Room* ret = r;

    if(direc == NULL)
    {
        return ret;
    }

    else if(strcmp(direc, "NORTH") == 0)
    {
        if(r->north != NULL)
        {
            if(r->north->open)
            {
                if(r->north->room_from == r)
                    ret = r->north->room_to;
                else
                    ret = r->north->room_from;
            }
            else
            {
                 printf("The door is shut\n");
            }

        }
        else
            printf("You can't move towards: %s\n", direc);
    }
    else if(strcmp(direc, "SOUTH") == 0)
    {
         if(r->north != NULL)
        {
            if(r->north->open)
            {
                if(r->north->room_from == r)
                    ret = r->north->room_to;
                else
                    ret = r->north->room_from;
            }
            else
            {
                 printf("The door is shut\n");
            }

        }
        else
            printf("You can't move towards: %s\n", direc);
    }
    else if(strcmp(direc, "EAST") == 0)
    {
         if(r->north != NULL)
        {
            if(r->north->open)
            {
                if(r->north->room_from == r)
                    ret = r->north->room_to;
                else
                    ret = r->north->room_from;
            }
            else
            {
                 printf("The door is shut\n");
            }

        }
        else
            printf("You can't move towards: %s\n", direc);
    }
    else if(strcmp(direc, "WEST") == 0)
    {
         if(r->north != NULL)
        {
            if(r->north->open)
            {
                if(r->north->room_from == r)
                    ret = r->north->room_to;
                else
                    ret = r->north->room_from;
            }
            else
            {
                 printf("The door is shut\n");
            }

        }
        else
            printf("You can't move towards: %s\n", direc);
    }

    return ret;
}

char* getRoomDesc(Room* r)
{
    return r->desc;
}

char *getRoomName(Room *r)
{
    return r->name;
}
