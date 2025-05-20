#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "string.h"

Object *objectInit(char *name, char *desc, uint8_t openable, uint8_t open, uint8_t carryable, uint8_t usable)
{
    Object* ret = calloc(sizeof(Object), 1);

    ret->name = name;
    ret->desc = desc;
    ret->openable = openable;
    ret->open = open;
    ret->carryable = carryable;
    ret->usable = usable;
    ret->usability = NULL; // Pointer to usability struct, NULL if not usable

    ret->nextObj = NULL;
    ret->prevObj = NULL;//

    return ret;
}

ObjectUsability* objectUsabilityInit()
{
    ObjectUsability* ret = malloc(sizeof(ObjectUsability));
    ret->usableRoomCount = 0;
    ret->usedRoomCount = 0;

    for(int i = 0; i < 5; i++)
    {
        ret->usableRooms[i] = NULL;
        ret->usedInRooms[i] = NULL;
    }

    return ret;
}

ObjectContainer *containerInit()
{
    ObjectContainer* ret = calloc(sizeof(ObjectContainer), 1);

    ret->headObject = NULL;
    ret->lastObject = NULL;

    return ret;
}

char *getName_Text(Object *o)
{
    char* buffer = calloc(1024 * sizeof(char), 1); 
    strcpy(buffer, "a ");
    strcat(buffer, o->name);
    if (o->openable)
    {
        if (o->open)
            strcat(buffer, " (open)");  
        else
            strcat(buffer, " (closed)");
    }
    strcat(buffer, "\n");
    return buffer;
}

char* getDesc_Text(Object* o)
{
    char* buffer = calloc(2048 * sizeof(char), 1); 
    strcpy(buffer, o->desc);
    if (o->openable)
    {
        if (o->open)
            strcat(buffer, "\n The object is open");  
        else
            strcat(buffer, "\n The object is closed");  
    }
    strcat (buffer, "\n");
    return buffer;
}

void addObject(ObjectContainer* c, Object* o)
{
    if(c->headObject == NULL)
    {
        c->headObject = o;
        c->lastObject = o;
    }
    else
    {
        c->lastObject->nextObj = o;
        o->prevObj = c->lastObject;
        c->lastObject = o;
    }
}

void removeObject(ObjectContainer* c, Object* o)
{
    if (c->headObject == o)
    {
        //set the head to the next object
        c->headObject = c->headObject->nextObj;
        if (c->headObject != NULL)
            c->headObject->prevObj = NULL;

        //if new head is null, tail is null too
        if(c->headObject == NULL)
            c->lastObject = NULL;
    }
    else
    {
        Object* next = c->headObject;
        while(next)
        {
            if(next == o)
            {
                if (next->prevObj)
                    next->prevObj->nextObj = next->nextObj;
                if (next->nextObj)
                    next->nextObj->prevObj = next->prevObj;
                // If removing the last object, update lastObject
                if (c->lastObject == next)
                    c->lastObject = next->prevObj;
                break; // done!
            }
            else
            {
                next = next->nextObj;
            }
        }
    }
}

void printContainer(ObjectContainer* c)
{
    Object* elem = c->headObject;
    if(elem == NULL)
    {
        printf("Your inventory is empty\n");
    }
    else{
        while(elem)
        {
            printf("%s", getName_Text(elem));
            printf("%s", getDesc_Text(elem));
            printf("\n\n");
            elem = elem->nextObj;
        }
    }
}