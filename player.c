#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "room.h"

Player *playerInit(Room *start, ObjectContainer *inventory)
{
    Player* ret = malloc(sizeof(Player));
    ret->currRoom = start;
    ret->inventory = inventory;
    return ret;
}

void MoveTo(Player *p, char *dest)
{   
    EDirection move = ERROR;

    for(size_t i = 0; i < Direction_Size-1; i++)
    {
        if(!(strcmp(dest, Direction_String[i])))
        {
            move = i;
        }
    }

    if (move == ERROR)
        printf("%s is not a valid direction \n", dest);
    else
    {
        p->currRoom = getRoom_Dir(p->currRoom, move);
        Look(p);
    }
}

void Look(Player* p)
{
    printf("%s\n", getRoomName(p->currRoom));
    printf("%s\n", getRoomDesc(p->currRoom));
}

void LookAt(char *ObjectName)
{

}

void Combine(Player *p, char *ObjectName1, char *ObjectName2)
{

}

void Put(Player *p, char *ObjectName1)
{
    
}

void Take(Player *p, char *ObjectName1)
{

}

void Inventory(Player *p)
{
    printContainer(p->inventory);
}

void Use(Player *p, char *ObjectName1)
{
}
