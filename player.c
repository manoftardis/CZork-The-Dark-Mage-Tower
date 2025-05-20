#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "room.h"
#include "utility.h"

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

//check if the object is in the room or in the inventory
//if in the room or in the inventory, print the description
void LookAt(Player* p, char *ObjectName)
{
    Object* obj = getObject(p, ObjectName);
    if(obj != NULL)
    {
        printf("%s\n", getDesc_Text(obj));
    }
    else
    {
        printf("%s is not a valid object \n", ObjectName);
    }
    
}

void Combine(Player *p, char *ObjectName1, char *ObjectName2)
{
    
}

void Put(Player *p, char *ObjectName1)
{
    Object* obj = getObjectFromContainer(p->inventory, ObjectName1);
    if(obj != NULL)
    {
        addObject(p->currRoom->inventory, obj);
        removeObject(p->inventory, obj);
        printf("You put the %s\n", obj->name);
    }
    else
    {
        printf("%s is not a valid object \n", ObjectName1);
    }
}

void Take(Player *p, char *ObjectName1)
{
    Object* obj = getObjectFromContainer(p->currRoom->inventory, ObjectName1);
    if(obj != NULL)
    {
        addObject(p->inventory, obj);
        removeObject(p->currRoom->inventory, obj);
        printf("You took the %s\n", obj->name);
    }
    else
    {
        printf("%s is not a valid object \n", ObjectName1);
    }
}

void Inventory(Player *p)
{
    printContainer(p->inventory);
}

// Helper to check if object is usable in current room
int isUsableInRoom(ObjectUsability* usability, Room* room) {
    if (!usability) return 0;
    for (int i = 0; i < usability->usableRoomCount; i++) {
        if (usability->usableRooms[i] == room) return 1;
    }
    return 0;
}

// Helper to check if object was already used in this room
int wasUsedInRoom(ObjectUsability* usability, Room* room) {
    if (!usability) return 0;
    for (int i = 0; i < usability->usedRoomCount; i++) {
        if (usability->usedInRooms[i] == room) return 1;
    }
    return 0;
}

// Helper to mark object as used in this room
void markUsedInRoom(ObjectUsability* usability, Room* room) {
    if (!usability) return;
    if (usability->usedRoomCount < 5) {
        usability->usedInRooms[usability->usedRoomCount++] = room;
    }
}

void Use(Player *p, char *ObjectName1)
{
    Object* obj = getObjectFromContainer(p->inventory, ObjectName1);
    if(obj == NULL) {
        printf("%s is not in your inventory.\n", ObjectName1);
        return;
    }
    if(!obj->usable || obj->usability == NULL) {
        printf("%s cannot be used.\n", ObjectName1);
        return;
    }
    if(!isUsableInRoom(obj->usability, p->currRoom)) {
        printf("You can't use %s here.\n", ObjectName1);
        return;
    }
    if(wasUsedInRoom(obj->usability, p->currRoom)) {
        printf("You have already used %s here.\n", ObjectName1);
        return;
    }
    // Mark as used
    markUsedInRoom(obj->usability, p->currRoom);

    // Perform the actual effect (customize per object/room)
    printf("You used the %s!\n", obj->name);
    if(strcmp(obj->name, "Crowbar") == 0) {
        if(strcmp(p->currRoom->name, "The Atrium") == 0) {
            printf("*You jam the rusty crowbar beneath the boards. "
                "With a loud creak and a shower of splinters, the planks give way, collapsing to the floor.\n"
                "The doorway to the cabin is now open.*\n");
            p->currRoom->west->open = 1;
        }
        else if(strcmp(p->currRoom->name, "Glass Cabinet") == 0) {
            printf("*You wedge the crowbar into the old hinge and apply pressure. "
                "With a loud snap, the cabinet swings open.\n" 
                "Inside, you retrieve the silvery-black \033[31mhair\033[0m. It's warm to the touch, unnaturally so.*\n");
            Object *temp = getObjectFromContainer(p->currRoom->inventory, "Glass Cabinet");
            temp->open = 1;
            }
    }
}

Object* getObject(Player *p, char *ObjectName)
{
    Object* obj = NULL;
    ObjectContainer* c = p->currRoom->inventory;
    if(c != NULL)
    {
        obj = getObjectFromContainer(c, ObjectName);
    }
    else
    {
        obj = getObjectFromContainer(p->inventory, ObjectName);
    }
    
    return obj;
}

Object* getObjectFromContainer(ObjectContainer* c, char* ObjectName)
{
    Object* obj = c->headObject;
    char objNameUpper[256];

    while(obj != NULL)
    {
        strncpy(objNameUpper, obj->name, sizeof(objNameUpper));
        objNameUpper[sizeof(objNameUpper)-1] = '\0';
        stringToUpper(objNameUpper);

        if(strcmp(objNameUpper, ObjectName) == 0)
        {
            return obj;
        }
        obj = obj->nextObj;
    }
    return NULL;
}

void Help()
{
    printf("Commands:\n");
    printf("MOVETO <direction>\n");
    printf("LOOK\n");
    printf("LOOKAT <object>\n");
    printf("TAKE <object>\n");
    printf("PUT <object>\n");
    printf("COMBINE <object1> <object2>\n");
    printf("USE <object>\n");
    printf("INVENTORY\n");
    printf("HELP\n");
}